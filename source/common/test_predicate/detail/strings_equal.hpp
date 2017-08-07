/// \file
/// \brief The strings_equal class header

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

#ifndef _CATH_TOOLS_SOURCE_COMMON_TEST_PREDICATE_STRINGS_EQUAL_H
#define _CATH_TOOLS_SOURCE_COMMON_TEST_PREDICATE_STRINGS_EQUAL_H

#include <boost/test/test_tools.hpp>

#include <string>

namespace cath {
	namespace test {
		namespace detail {

			size_t index_of_first_difference(const std::string &,
			                                 const std::string &);

			boost::test_tools::predicate_result strings_equal(const std::string &,
			                                                  const std::string &,
			                                                  const std::string &,
			                                                  const std::string &,
			                                                  const size_t &);

		} // namespace detail
	} // namespace test
} // namespace cath


#endif