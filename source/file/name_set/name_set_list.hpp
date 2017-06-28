/// \file
/// \brief The name_set_list class header

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

#ifndef _CATH_TOOLS_SOURCE_FILE_NAME_SET_LIST_NAME_SET_LIST_H
#define _CATH_TOOLS_SOURCE_FILE_NAME_SET_LIST_NAME_SET_LIST_H

#include "common/cpp14/cbegin_cend.hpp"
#include "file/file_type_aliases.hpp"
#include "file/name_set/name_set.hpp"

namespace cath {

	/// A type alias for a vector of name_set objects
	///
	/// \TODO Move to common/type_aliases.hpp
	using str_opt_vec = std::vector<str_opt>;

	namespace file {

		/// \brief A list of name_set objects
		class name_set_list final {
		private:
			/// \brief The vector of name_sets
			name_set_vec name_sets;

		public:
			/// \brief A const_iterator type alias as part of making this a range over name_sets
			using const_iterator = name_set_vec::const_iterator;

			/// \brief Ctor
			name_set_list() noexcept = default;
			explicit name_set_list(name_set_vec);

			bool empty() const;
			size_t size() const;

			const name_set & operator[](const size_t &) const;

			const_iterator begin() const;
			const_iterator end() const;
		};

		/// \brief Ctor from vector of name_sets
		inline name_set_list::name_set_list(name_set_vec arg_name_sets ///< The vector of name_sets from which to construct this name_set_list
		                                    ) : name_sets{ std::move( arg_name_sets ) } {
		}

		/// \brief Return whether this is empty
		inline bool name_set_list::empty() const {
			return name_sets.empty();
		}

		/// \brief Return the number of name_sets
		inline size_t name_set_list::size() const {
			return name_sets.size();
		}

		/// \brief Return the name_set stored at the specified index
		inline const name_set & name_set_list::operator[](const size_t &arg_index ///< The index of the name_set to return
		                                                  ) const {
			return name_sets[ arg_index ];
		}

		/// \brief Standard const begin() method, as part of making this into a range over the name_sets
		inline auto name_set_list::begin() const -> const_iterator {
			return common::cbegin( name_sets );
		}

		/// \brief Standard const end() method, as part of making this into a range over the name_sets
		inline auto name_set_list::end() const -> const_iterator {
			return common::cend  ( name_sets );
		}

		name_set_list build_name_set_list(str_vec,
		                                  str_vec,
		                                  str_opt_vec);

		std::string to_string(const name_set_list &);

		std::ostream & operator<<(std::ostream &,
		                          const name_set_list &);

		str_vec get_names_from_acq(const name_set_list &);

		str_vec get_alignment_html_names(const name_set_list &);
		str_vec get_multi_ssap_alignment_file_names(const name_set_list &);
		str_vec get_supn_json_names(const name_set_list &);
		str_vec get_supn_pdb_file_names(const name_set_list &);
		str_vec get_viewer_names(const name_set_list &);

	} // namespace file
} // namespace cath

#endif
