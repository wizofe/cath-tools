/// \file
/// \brief The read_domain_def_from_pdb class definitions

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

#include "read_domain_def_from_pdb.hpp"

#include "chopping/domain/domain_definition.hpp"
#include "common/exception/not_implemented_exception.hpp"
#include "file/data_file.hpp"
#include "file/options/data_dirs_spec.hpp"
#include "file/pdb/pdb.hpp"

using namespace cath::chop;
using namespace cath::common;
using namespace cath::file;
using namespace cath::opts;

using boost::filesystem::path;
using std::make_pair;
using std::pair;

/// \brief TODOCUMENT
pair<path, pdb> cath::file::read_domain_from_pdb(const domain_definition &arg_read_domain_def_from_pdb, ///< TODOCUMENT
                                                 const data_dirs_spec    &arg_data_dirs_spec            ///< TODOCUMENT
                                                 ) {
	const path pdb_file = find_file(
		arg_data_dirs_spec,
		data_file::PDB,
		arg_read_domain_def_from_pdb.get_pdb_name()
	);
	return make_pair(
		pdb_file,
		read_domain_from_pdb_file(
			pdb_file,
			arg_read_domain_def_from_pdb.get_domain()
		)
	);
}

/// \brief TODOCUMENT
///
/// \relates pdb
///
/// \relatesalso domain
pdb cath::file::read_domain_from_pdb_file(const path   &arg_pdb_filename, ///< TODOCUMENT
                                          const domain &/*arg_domain*/    ///< TODOCUMENT
                                          ) {
	BOOST_THROW_EXCEPTION(not_implemented_exception("This is not implemented this here"));
	pdb new_pdb;
	new_pdb.read_file( arg_pdb_filename );
	return new_pdb;
}
