/// \file
/// \brief The json_file_superposition_outputter class definitions

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

#include "json_file_superposition_outputter.h"

#include "common/clone/make_uptr_clone.h"
#include "common/file/open_fstream.h"
#include "superposition/superposition_context.h"

#include <fstream>

using namespace boost::filesystem;
using namespace cath::common;
using namespace cath::opts;
using namespace cath::sup;
using namespace std;

constexpr sup_json_style json_file_superposition_outputter::DEFAULT_JSON_STYLE;

/// \brief A standard do_clone method.
unique_ptr<superposition_outputter> json_file_superposition_outputter::do_clone() const {
	return { make_uptr_clone( *this ) };
}

/// \brief TODOCUMENT
void json_file_superposition_outputter::do_output_superposition(const superposition_context &arg_superposition_context, ///< The superpositon_context object to output
                                                                ostream                     &/*arg_ostream*/            ///< An ostream object to which any warnings/errors may be written (currently ignored)
                                                                ) const {
	ofstream json_file_ostream;
	open_ofstream( json_file_ostream, output_file );
	json_file_ostream << to_json_string( arg_superposition_context, ( json_style == sup_json_style::PRETTY ) );
	json_file_ostream << flush;
	json_file_ostream.close();
}

/// \brief Specify that this outputter doesn't involve a display_spec
bool json_file_superposition_outputter::do_involves_display_spec() const {
	return false;
}

/// \brief Ctor for json_file_superposition_outputter
json_file_superposition_outputter::json_file_superposition_outputter(const path           &arg_output_file, ///< The file to which the superposition should be written
                                                                     const sup_json_style &arg_json_style   ///< The style in which the JSON should be written
                                                                     ) : output_file ( arg_output_file  ),
                                                                         json_style  ( arg_json_style   ) {
}
