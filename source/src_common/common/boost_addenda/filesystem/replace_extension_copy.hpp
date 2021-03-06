/// \file
/// \brief The replace_extension_copy header

/// \copyright
/// Tony Lewis's Common C++ Library Code (here imported into the CATH Tools project and then tweaked, eg namespaced in cath)
/// Copyright (C) 2007, Tony Lewis
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

#ifndef _CATH_TOOLS_SOURCE_SRC_COMMON_COMMON_BOOST_ADDENDA_FILESYSTEM_REPLACE_EXTENSION_COPY_HPP
#define _CATH_TOOLS_SOURCE_SRC_COMMON_COMMON_BOOST_ADDENDA_FILESYSTEM_REPLACE_EXTENSION_COPY_HPP

#include <boost/filesystem/path.hpp>

namespace cath {
	namespace common {

		/// \brief Return a copy of the specified path in which the extension has been
		///        replaced with the specified replacement
		inline boost::filesystem::path replace_extension_copy(boost::filesystem::path        arg_file,
		                                                      const boost::filesystem::path &arg_replacement = boost::filesystem::path()
		                                                      ) {
			arg_file.replace_extension( arg_replacement );
			return arg_file;
		}

	} // namespace common
} // namespace cath

#endif
