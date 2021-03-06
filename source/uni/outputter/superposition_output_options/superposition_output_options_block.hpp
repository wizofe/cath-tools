/// \file
/// \brief The superposition_output_options_block class header

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

#ifndef _CATH_TOOLS_SOURCE_UNI_OUTPUTTER_SUPERPOSITION_OUTPUT_OPTIONS_SUPERPOSITION_OUTPUT_OPTIONS_BLOCK_HPP
#define _CATH_TOOLS_SOURCE_UNI_OUTPUTTER_SUPERPOSITION_OUTPUT_OPTIONS_SUPERPOSITION_OUTPUT_OPTIONS_BLOCK_HPP

#include <boost/ptr_container/ptr_vector.hpp>

#include "options/options_block/options_block.hpp"
#include "superposition/superposition_content_spec.hpp"

#include <iosfwd>

namespace cath { class display_spec; }
namespace cath { namespace opts { class superposition_outputter; } }
namespace cath { namespace opts { class superposition_outputter_list; } }
namespace cath { namespace sup { class superposition_content_spec; } }

namespace superposition_output_options_block_test_suite { struct parses_option_for_to_json_file; }
namespace superposition_output_options_block_test_suite { struct unparsed_has_no_json_file; }

namespace cath {
	namespace opts {

		/// \brief What superposition outputter (if any) should be provided if none is explicitly specified
		enum class default_supn_outputter : bool {
			PYMOL, ///< The pymol_view_superposition_outputter
			NONE   ///< No outputter
		};

		/// \brief TODOCUMENT
		class superposition_output_options_block final : public options_block {
		private:
			friend struct superposition_output_options_block_test_suite::parses_option_for_to_json_file;
			friend struct superposition_output_options_block_test_suite::unparsed_has_no_json_file;

			using super = options_block;

			static const std::string DEFAULT_PYMOL_PROGRAM;

			boost::filesystem::path sup_to_pdb_file;
			boost::filesystem::path sup_to_pdb_files_dir;
			bool sup_to_stdout;
			bool sup_to_pymol;
			boost::filesystem::path sup_to_pymol_file;
			boost::filesystem::path pymol_program;
			boost::filesystem::path json_file;

			std::unique_ptr<options_block> do_clone() const final;
			std::string do_get_block_name() const final;
			void do_add_visible_options_to_description(boost::program_options::options_description &,
			                                           const size_t &) final;
			str_opt do_invalid_string(const boost::program_options::variables_map &) const final;
			str_vec do_get_all_options_names() const final;

			boost::filesystem::path get_sup_to_pdb_file() const;
			boost::filesystem::path get_sup_to_pdb_files_dir() const;
			bool get_sup_to_stdout() const;
			bool get_sup_to_pymol() const;
			boost::filesystem::path get_pymol_program() const;
			boost::filesystem::path get_sup_to_pymol_file() const;
			boost::filesystem::path get_json_file() const;

		public:
			static const std::string PO_SUP_FILE;
			static const std::string PO_SUP_FILES_DIR;
			static const std::string PO_SUP_TO_STDOUT;
			static const std::string PO_SUP_TO_PYMOL;
			static const std::string PO_PYMOL_PROGRAM;
			static const std::string PO_SUP_TO_PYMOL_FILE;
			static const std::string PO_SUP_TO_JSON_FILE;

			/// \todo Consider adding a sister get_superposition_outputters() for getting outputters
			///       that don't require a display_spec / superposition_content_spec
			superposition_outputter_list get_superposition_outputters(const display_spec &,
			                                                          const sup::superposition_content_spec & = sup::superposition_content_spec{},
			                                                          const default_supn_outputter & = default_supn_outputter::NONE) const;
			bool outputs_to_stdout() const;
		};
	} // namespace opts
} // namespace cath

#endif
