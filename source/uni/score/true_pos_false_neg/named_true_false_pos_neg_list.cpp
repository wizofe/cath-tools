/// \file
/// \brief The named_true_false_pos_neg_list class definitions

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

#include "named_true_false_pos_neg_list.hpp"

#include "score/true_pos_false_neg/classn_stat.hpp"
#include "score/true_pos_false_neg/classn_stat_pair_series.hpp"
#include "score/true_pos_false_neg/true_false_pos_neg.hpp"

#include <utility>

using namespace cath;
using namespace cath::score;
using namespace std;

/// \brief TODOCUMENT
named_true_false_pos_neg_list::named_true_false_pos_neg_list(true_false_pos_neg_list arg_list, ///< TODOCUMENT
                                                             string                  arg_name  ///< TODOCUMENT
                                                             ) : the_list { std::move( arg_list ) },
                                                                 name     { std::move( arg_name ) } {
}

/// \brief Ctor from true_false_pos_neg_vec and string containing the name
///
/// This delegates to the previous ctor. It could easily just initialise the member itself but
/// delegation is preferred so that this ctor doesn't have to repeat any post-initialisation steps added
/// to the previous one.
named_true_false_pos_neg_list::named_true_false_pos_neg_list(true_false_pos_neg_vec arg_list, ///< TODOCUMENT
                                                             string                 arg_name  ///< TODOCUMENT
                                                             ) : named_true_false_pos_neg_list{
                                                                 	true_false_pos_neg_list{ std::move( arg_list ) },
                                                                 	std::move( arg_name )
                                                                 } {
}

/// \brief TODOCUMENT
const true_false_pos_neg_list & named_true_false_pos_neg_list::get_list() const {
	return the_list;
}

/// \brief TODOCUMENT
const string & named_true_false_pos_neg_list::get_name() const {
	return name;
}

/// \brief TODOCUMENT
///
/// \relates named_true_false_pos_neg_list
size_rational cath::score::get_classn_stat_val_of_index(const named_true_false_pos_neg_list &arg_tfpns,       ///< TODOCUMENT
                                                        const classn_stat                   &arg_classn_stat, ///< TODOCUMENT
                                                        const size_t                        &arg_index        ///< TODOCUMENT
                                                        ) {
	return get_classn_stat_val_of_index( arg_tfpns.get_list(), arg_classn_stat, arg_index );
}

/// \brief TODOCUMENT
///
/// \relates named_true_false_pos_neg_list
size_rational_vec cath::score::get_classn_stat_vals(const named_true_false_pos_neg_list &arg_tfpns,      ///< TODOCUMENT
                                                    const classn_stat                   &arg_classn_stat ///< TODOCUMENT
                                                    ) {
	return get_classn_stat_vals( arg_tfpns.get_list(), arg_classn_stat );
}

/// \brief TODOCUMENT
///
/// \relates named_true_false_pos_neg_list
classn_stat_pair_series cath::score::get_classn_stat_pair_series(const named_true_false_pos_neg_list &arg_tfpns,         ///< TODOCUMENT
                                                                 const classn_stat                   &arg_classn_stat_a, ///< TODOCUMENT
                                                                 const classn_stat                   &arg_classn_stat_b  ///< TODOCUMENT
                                                                 ) {
	return get_classn_stat_pair_series( arg_tfpns.get_list(), arg_tfpns.get_name(), arg_classn_stat_a, arg_classn_stat_b );
}

/// \brief TODOCUMENT
///
/// \relates named_true_false_pos_neg_list
double cath::score::area_under_curve(const named_true_false_pos_neg_list &arg_tfpns,         ///< TODOCUMENT
                                     const classn_stat                   &arg_classn_stat_x, ///< TODOCUMENT
                                     const classn_stat                   &arg_classn_stat_y  ///< TODOCUMENT
                                     ) {
	return area_under_curve( arg_tfpns.get_list(), arg_classn_stat_x, arg_classn_stat_y );
}

/// \brief TODOCUMENT
///
/// \relates true_false_pos_neg_list
classn_stat_pair_series cath::score::get_roc_series(const named_true_false_pos_neg_list &arg_tfpns ///< TODOCUMENT
//                                                    const string                        &arg_name   ///< TODOCUMENT
                                                    ) {
	return get_roc_series( arg_tfpns.get_list(), arg_tfpns.get_name() );
}

/// \brief TODOCUMENT
///
/// \relates named_true_false_pos_neg_list
double cath::score::area_under_roc_curve(const named_true_false_pos_neg_list &arg_tfpns ///< TODOCUMENT
                                         ) {
	return area_under_roc_curve( arg_tfpns.get_list() );
}
