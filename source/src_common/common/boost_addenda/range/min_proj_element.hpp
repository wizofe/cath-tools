/// \file
/// \brief The min_proj_element header

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

#ifndef _CATH_TOOLS_SOURCE_SRC_COMMON_COMMON_BOOST_ADDENDA_RANGE_MIN_PROJ_ELEMENT_HPP
#define _CATH_TOOLS_SOURCE_SRC_COMMON_COMMON_BOOST_ADDENDA_RANGE_MIN_PROJ_ELEMENT_HPP

#include <boost/range/algorithm/min_element.hpp>

#include "common/boost_addenda/range/range_concept_type_aliases.hpp"
#include "common/function/ident.hpp"

namespace cath {
	namespace common {

		/// \brief Wrap boost::range::min_element() and add support for a projection function, a la Eric Niebler's range-v3 library
		///
		/// \todo Roll this out to simplify code
		template <typename Rng,
		          typename Pred = std::less<>,
		          typename Proj = ident>
		inline auto min_proj_element(Rng  &&arg_range,          ///< The range to query
		                             Pred &&arg_pred  = Pred{}, ///< The less-than predicate function
		                             Proj &&arg_proj  = Proj{}  ///< The projection function
		                             ) {
			return boost::range::min_element(
				arg_range,
				[&] (const auto & x, const auto & y) {
					return std::forward<Pred>( arg_pred )( arg_proj( x ), arg_proj( y ) );
				}
			);
		}

		/// \brief Return the projection of the min_proj_element() of the specified range
		///
		/// \todo Roll this out to simplify code
		template <typename Rng,
		          typename Pred = std::less<>,
		          typename Proj = ident>
		inline auto min_proj(Rng  &&arg_range,          ///< The range to query
		                     Pred &&arg_pred  = Pred{}, ///< The less-than predicate function
		                     Proj &&arg_proj  = Proj{}  ///< The projection function
		                     ) {
			return arg_proj( *min_proj_element(
				std::forward< Rng  >( arg_range ),
				std::forward< Pred >( arg_pred  ),
				std::forward< Proj >( arg_proj  )
			) );
		}

	} // namespace common
} // namespace cath

#endif
