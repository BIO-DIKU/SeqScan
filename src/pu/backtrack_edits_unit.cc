/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "backtrack_edits_unit.h"

#include <utility>
#include <iostream>

using namespace std;


BacktrackEditsUnit::BacktrackEditsUnit(
    const Modifiers &modifiers,
    const std::string& pattern
) :
    PatternUnit(modifiers),
    pattern_(pattern)
{ }

void BacktrackEditsUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;

  last_found_matches_.clear();
  last_found_index_ = 0;
}

bool BacktrackEditsUnit::FindMatch() {
  if (sequence_iterator_ == sequence_iterator_end_) return false;

  if (stay_at_pos_) {
    // TODO(Ras) This is a little ugly. Clean up when not tired
    if (last_found_index_ != 0 && last_found_index_ + 1 >= last_found_matches_.size()) {
      return false;
    }

    if (last_found_matches_.empty()) {
      int E = modifiers_.max_edits_;

      CollectMatches(sequence_iterator_, pattern_.cbegin(), E, 0);
      if (last_found_matches_.empty()) {
        last_found_index_++;
        return false;
      } else {
        return true;
      }
    }
    last_found_index_++;
    return last_found_index_ < last_found_matches_.size();
  }

  if (last_found_index_ + 1 >= last_found_matches_.size()) {

    // All previously identified matches have been iterated through. Time to
    // look for new ones.
    last_found_matches_.clear();
    last_found_index_ = 0;

    int E = modifiers_.max_edits_;

    while (sequence_iterator_ != sequence_iterator_end_) {
      CollectMatches(sequence_iterator_, pattern_.cbegin(), E, 0);

      ++sequence_iterator_;

      if (!last_found_matches_.empty())
        return true;
    }

    return false;

  } else {
    last_found_index_++;
    return true;
  }
}

const Match& BacktrackEditsUnit::GetMatch() const {
  std::set<Match >::iterator it = last_found_matches_.begin();
  std::advance(it, last_found_index_);
  return *it;
}

void BacktrackEditsUnit::CollectMatches(
    std::string::const_iterator seq_it,
    std::string::const_iterator pat_it,
    const int E_left,
    const int E_used
) {
  // std::cout<<"CollectMatches("<<(seq_it-sequence_iterator_)<<", "<<
  //    (pat_it-pattern_.cbegin())<<", Mleft:"<<M_left<<", Ileft:"<<I_left<<", "
  //    "Dleft:"<<D_left<<", Mused:"<<M_used<<", Iused:"<<I_used<<", "
  //    "Dused:"<<D_used<<" )"<<std::endl;

  //if (E_left > 0) CollectMatches(seq_it + 1, pat_it, E_left - 1, E_used + 1);

  if (pat_it == pattern_.cend()) {
    last_found_matches_.insert(
        Match(sequence_iterator_, pattern_.length()+0, E_used)); //TODO: Calc correct length
    return;
  }

  if (seq_it == sequence_iterator_end_)
    return;

  if (modifiers_.res_matcher_.Match(*seq_it,*pat_it)) {
    CollectMatches(seq_it + 1, pat_it + 1, E_left, E_used);
    return;
  }

  if (E_left > 0) {
    CollectMatches(seq_it + 1, pat_it + 1, E_left - 1, E_used + 1); // Check if mismatch
    CollectMatches(seq_it    , pat_it + 1, E_left - 1, E_used + 1); // Check if insertion
    CollectMatches(seq_it + 1, pat_it    , E_left - 1, E_used + 1); // Check if deletion
  }


}

std::ostream& operator<<(std::ostream& os, const BacktrackEditsUnit& obj) {
  return obj.Print(os);
}
std::ostream& BacktrackEditsUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);
  // if(modifiers_.label_.size()>0)
  //   os<<modifiers_.label_<<"=";

  os << pattern_;

  modifiers_.PrintPUSuffix(os);
  // if (modifiers_.mismatches_ ||
  //     modifiers_.insertions_ ||
  //     modifiers_.deletions_) {
  //  os << "/" << modifiers_.mismatches_ << "," <<
  //               modifiers_.insertions_ << "," <<
  //               modifiers_.deletions_;
  //}

  return os;
}

std::unique_ptr<PatternUnit> BacktrackEditsUnit::Clone() const {
  std::unique_ptr<PatternUnit> ret( new BacktrackEditsUnit(modifiers_, pattern_) );
  return std::move(ret);
}

