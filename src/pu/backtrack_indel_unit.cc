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

#include "backtrack_indel_unit.h"

#include <utility>
#include <iostream>

using namespace std;


BacktrackIndelUnit::BacktrackIndelUnit(
    const Modifiers &modifiers,
    const std::string& pattern
) :
    PatternUnit(modifiers),
    pattern_(pattern)
{ }

void BacktrackIndelUnit::Initialize(
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

bool BacktrackIndelUnit::FindMatch() {
  if (sequence_iterator_ == sequence_iterator_end_) return false;

  if (stay_at_pos_) {
    // TODO(Ras) This is a little ugly. Clean up when not tired
    if (last_found_index_ != 0 && last_found_index_ + 1 >= last_found_matches_.size()) {
      return false;
    }

    if (last_found_matches_.empty()) {
      int M  = modifiers_.mismatches_;
      int ID = modifiers_.indels_;

      CollectMatches(sequence_iterator_, pattern_.cbegin(), M, ID, 0, 0, 0);
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

    int M  = modifiers_.mismatches_;
    int ID = modifiers_.indels_;

    while (sequence_iterator_ != sequence_iterator_end_) {
      CollectMatches(sequence_iterator_, pattern_.cbegin(), M, ID, 0, 0, 0);

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

const Match& BacktrackIndelUnit::GetMatch() const {
  std::set<Match >::iterator it = last_found_matches_.begin();
  std::advance(it, last_found_index_);
  return *it;
}

void BacktrackIndelUnit::CollectMatches(
    std::string::const_iterator seq_it,
    std::string::const_iterator pat_it,
    const int M_left, const int ID_left,
    const int M_used, const int I_used, const int D_used
) {


  if (pat_it == pattern_.cend()) {
    last_found_matches_.insert(
        Match(sequence_iterator_, pattern_.length() + I_used - D_used, M_used + I_used + D_used ));
    return;
  }

  if (seq_it == sequence_iterator_end_)
    return;

  if (ID_left > 0) {
    CollectMatches(seq_it  , pat_it+1, M_left, ID_left-1, M_used, I_used+1 , D_used);
    CollectMatches(seq_it+1, pat_it  , M_left, ID_left-1, M_used, I_used   , D_used+1);
  }

  if (modifiers_.res_matcher_.Match(*seq_it,*pat_it)) {
    CollectMatches(seq_it + 1, pat_it + 1, M_left, ID_left, M_used, I_used, D_used);
    return;
  }

  if (M_left > 0) CollectMatches(seq_it + 1, pat_it + 1, M_left - 1, ID_left, M_used + 1, I_used, D_used);
}

std::ostream& operator<<(std::ostream& os, const BacktrackIndelUnit& obj) {
  return obj.Print(os);
}
std::ostream& BacktrackIndelUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);
  os << pattern_;
  modifiers_.PrintPUSuffix(os);

  return os;
}

std::unique_ptr<PatternUnit> BacktrackIndelUnit::Clone() const {
  std::unique_ptr<PatternUnit> ret( new BacktrackIndelUnit(modifiers_, pattern_) );
  return std::move(ret);
}

