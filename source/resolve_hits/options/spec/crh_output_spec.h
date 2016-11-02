/// \file
/// \brief The crh_output_spec class header

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

#ifndef _CATH_TOOLS_SOURCE_RESOLVE_HITS_OPTIONS_SPEC_CRH_OUTPUT_SPEC_H
#define _CATH_TOOLS_SOURCE_RESOLVE_HITS_OPTIONS_SPEC_CRH_OUTPUT_SPEC_H

#include <boost/optional.hpp>

#include "common/path_type_aliases.h"
#include "common/type_aliases.h"
#include "resolve_hits/options/spec/hit_boundary_output.h"

namespace cath {
	namespace rslv {

		/// \brief Specify the output for cath-resolve-hits
		class crh_output_spec final {
		private:
			/// \brief The output file to which data should be written
			path_opt            output_file;

			/// \brief Whether to output the hits starts/stops *after* trimming
			hit_boundary_output boundary_output      = DEFAULT_BOUNDARY_OUTPUT;

			/// \brief Whether to output HTML describing the hits and the results
			bool                generate_html_output = DEFAULT_GENERATE_HTML_OUTPUT;

		public:
			/// \brief The default value for whether to output the hits starts/stops *after* trimming
			static constexpr hit_boundary_output DEFAULT_BOUNDARY_OUTPUT      = hit_boundary_output::ORIG;

			/// \brief The default value for whether to output HTML describing the hits and the results
			static constexpr bool                DEFAULT_GENERATE_HTML_OUTPUT = false;

			const path_opt & get_output_file() const;
			const hit_boundary_output & get_boundary_output() const;
			const bool & get_generate_html_output() const;

			crh_output_spec & set_output_file(const boost::filesystem::path &);
			crh_output_spec & set_boundary_output(const hit_boundary_output &);
			crh_output_spec & set_generate_html_output(const bool &);
		};

		str_opt get_invalid_description(const crh_output_spec &);

		crh_output_spec & set_output_trimmed_hits(crh_output_spec &,
		                                          const bool &);

	} // namespace rslv
} // namespace cath

#endif