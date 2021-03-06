/// \file
/// \brief The html_ostream_alignment_outputter class definitions

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


#include "html_ostream_alignment_outputter.hpp"

#include "alignment/alignment_context.hpp"
#include "alignment/io/alignment_io.hpp"
#include "alignment/io/outputter/html_align_outputter.hpp"
#include "chopping/region/region.hpp"
#include "common/clone/make_uptr_clone.hpp"
#include "display/options/display_spec.hpp"
#include "display_colour/display_colour.hpp"
#include "file/pdb/pdb.hpp"
#include "file/pdb/pdb_atom.hpp"
#include "file/pdb/pdb_residue.hpp"
#include "structure/protein/protein.hpp"
#include "structure/protein/protein_list.hpp"
#include "structure/protein/residue.hpp"
#include "structure/protein/sec_struc.hpp"
#include "structure/protein/sec_struc_planar_angles.hpp"

using namespace cath::align;
using namespace cath::common;
using namespace cath::opts;
using namespace std;

/// \brief A standard do_clone method.
unique_ptr<alignment_outputter> html_ostream_alignment_outputter::do_clone() const {
	return { make_uptr_clone( *this ) };
}

/// \brief TODOCUMENT
void html_ostream_alignment_outputter::do_output_alignment(const alignment_context &arg_alignment_context, ///< TODOCUMENT
                                                           ostream                 &arg_ostream            ///< TODOCUMENT
                                                           ) const {
	arg_ostream << make_html_align_outputter( arg_alignment_context, *colourer_ptr ) << flush;
}

/// \brief TODOCUMENT
bool html_ostream_alignment_outputter::do_involves_display_spec() const {
	return true;
}

/// \brief Ctor for html_ostream_alignment_outputter
html_ostream_alignment_outputter::html_ostream_alignment_outputter(const display_colourer &arg_colourer ///< TODOCUMENT
                                                                   ) : colourer_ptr( arg_colourer.clone() ) {
}

/// \brief TODOCUMENT
html_ostream_alignment_outputter cath::opts::make_html_ostream_alignment_outputter(const display_spec &arg_display_spec ///< TODOCUMENT
                                                                                   ) {
	return html_ostream_alignment_outputter( *get_display_colourer( arg_display_spec, make_default_light_colour_gradient() ) );
}

/// \brief Get a name for this alignment_outputter
string html_ostream_alignment_outputter::do_get_name() const {
	return "HTML";
}
