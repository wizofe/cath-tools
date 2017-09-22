/// \file
/// \brief The ssap_scores_file_alignment_acquirer class definitions

/// \copyright
/// CATH Tools - Protein structure comparison tools such as SSAP and SNAP
/// Copyright (C) 2011, Orengo Group, University College London
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "ssap_scores_file_alignment_acquirer.hpp"

#include "alignment/alignment.hpp"
#include "alignment/alignment_action.hpp"
#include "alignment/io/alignment_io.hpp"
#include "alignment/io/outputter/horiz_align_outputter.hpp" /// *** TEMPORARY? ***
#include "alignment/residue_score/residue_scorer.hpp"
#include "common/boost_addenda/range/front.hpp"
#include "common/clone/make_uptr_clone.hpp"
#include "common/file/open_fstream.hpp"
#include "file/pdb/pdb.hpp"
#include "file/pdb/pdb_atom.hpp"
#include "file/pdb/pdb_list.hpp"
#include "file/pdb/pdb_residue.hpp"
#include "file/pdb/protein_info.hpp"
#include "file/ssap_scores_file/ssap_scores_file.hpp"
#include "structure/protein/protein.hpp"
#include "structure/protein/protein_list.hpp"
#include "structure/protein/residue.hpp"
#include "structure/protein/sec_struc.hpp"               /// *** TEMPORARY? ***
#include "structure/protein/sec_struc_planar_angles.hpp" /// *** TEMPORARY? ***
#include "superposition/superpose_orderer.hpp"

#include <fstream>

using namespace cath::align;
using namespace cath::common;
using namespace cath::file;
using namespace cath::sup;
using namespace cath::opts;
using namespace std;

using boost::filesystem::path;

/// \brief A standard do_clone method.
unique_ptr<alignment_acquirer> ssap_scores_file_alignment_acquirer::do_clone() const {
	return { make_uptr_clone( *this ) };
}

/// \brief TODOCUMENT
pair<alignment, superpose_orderer> ssap_scores_file_alignment_acquirer::do_get_alignment_and_orderer(const pdb_list &arg_pdbs ///< TODOCUMENT
                                                                                                     ) const {
	// Parse the SSAP scores file
	const path                     ssaps_filename = get_ssap_scores_file();
	const pair<str_vec, size_size_pair_doub_map> ssap_scores_data = ssap_scores_file::parse_ssap_scores_file( ssaps_filename );
	const str_vec                 &names            = ssap_scores_data.first;
	const size_size_pair_doub_map &scores           = ssap_scores_data.second;

	if ( names.size() != arg_pdbs.size() ) {
		BOOST_THROW_EXCEPTION(runtime_error_exception(
			"The number of PDBs is "
			+ ::std::to_string( arg_pdbs.size()         )
			+ ", which doesn't match the "
			+ ::std::to_string( names.size() )
			+ " structures required for combining with the SSAP scores file \""
			+ ssaps_filename.string()
			+ "\""
		));
	}

	// Make a superpose_orderer from the scores
	const superpose_orderer my_orderer = make_superpose_orderer( scores );

	// Use the superpose_orderer code to get a spanning tree, ordered in descending order of score
	const size_size_pair_vec spanning_tree = get_spanning_tree_ordered_by_desc_score( scores );

//	// TODOCUMENT
	ostringstream stderr;
	const size_size_alignment_tuple_vec spanning_alignments = get_spanning_alignments(
		ssaps_filename.parent_path(),
		names,
		arg_pdbs,
		spanning_tree,
		stderr
	);

	// TODOCUMENT
	const bool      single_pdb    = ( arg_pdbs.size() == 1 );
	const alignment new_alignment = single_pdb ? make_single_alignment( front( arg_pdbs ).get_num_residues() )
	                                           : build_alignment_from_parts( spanning_alignments, build_protein_list_of_pdb_list( arg_pdbs ) );

	if ( names.empty() ) {
		// Return the results
		return make_pair( new_alignment, my_orderer );
	}

//	BOOST_LOG_TRIVIAL( warning )<< "About to attempt to build protein list using data that's been read from ssaps_filename (with " << arg_pdbs.size() << " pdbs and " << names.size() << " names)";

	const protein_list proteins_of_pdbs     = build_protein_list_of_pdb_list_and_names( arg_pdbs, names );
	const alignment    scored_new_alignment = score_alignment_copy( residue_scorer(), new_alignment, proteins_of_pdbs );


//	cerr << "Did generate alignment : \n";
//	cerr << horiz_align_outputter( scored_new_alignment ) << endl;
//	write_alignment_as_fasta_alignment( cerr, scored_new_alignment, build_protein_list_of_pdb_list( arg_pdbs ) );
//	cerr << endl;

	// Return the results
	return make_pair( scored_new_alignment, my_orderer );
}

/// \brief TODOCUMENT
///
/// \TODO Consider taking an ostream_ref_opt argument rather than ostream
///       (fix all errors, *then* provide default of boost::none)
size_size_alignment_tuple_vec ssap_scores_file_alignment_acquirer::get_spanning_alignments(const path               &arg_alignment_dir, ///< TODOCUMENT
                                                                                           const str_vec            &arg_names,         ///< TODOCUMENT
                                                                                           const pdb_list           &arg_pdbs,          ///< TODOCUMENT
                                                                                           const size_size_pair_vec &arg_spanning_tree, ///< TODOCUMENT
                                                                                           ostream                  &arg_stderr         ///< TODOCUMENT
                                                                                           ) const {
	size_size_alignment_tuple_vec spanning_alignments;
	spanning_alignments.reserve( spanning_alignments.size() );
	for (const size_size_pair &spanning_branch : arg_spanning_tree) {
		const size_t   &first_index    = spanning_branch.first;
		const size_t   &second_index   = spanning_branch.second;
		const pdb      &first_pdb      = arg_pdbs [ first_index  ];
		const pdb      &second_pdb     = arg_pdbs [ second_index ];
		const string   &first_name     = arg_names[ first_index  ];
		const string   &second_name    = arg_names[ second_index ];
		const path      alignment_file = arg_alignment_dir / ( first_name + second_name + ".list" );
		const alignment new_alignment  = read_alignment_from_cath_ssap_legacy_format(
			alignment_file,
			build_protein_of_pdb( first_pdb,  ref( arg_stderr ) ).first,
			build_protein_of_pdb( second_pdb, ref( arg_stderr ) ).first,
			arg_stderr
		);
		spanning_alignments.emplace_back(
			first_index,
			second_index,
			new_alignment
		);
	}
	return spanning_alignments;
}

/// \brief Ctor for ssap_scores_file_alignment_acquirer
ssap_scores_file_alignment_acquirer::ssap_scores_file_alignment_acquirer(const path &arg_ssap_scores_filename ///< TODOCUMENT
                                                                         ) : ssap_scores_filename{ arg_ssap_scores_filename } {
}

/// \brief TODOCUMENT
path ssap_scores_file_alignment_acquirer::get_ssap_scores_file() const {
	return ssap_scores_filename;
}

