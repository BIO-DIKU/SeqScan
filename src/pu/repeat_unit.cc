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

#include "repeat_unit.h"

RepeatUnit::RepeatUnit(
    std::unique_ptr<PatternUnit>& pu,
    const Modifiers &modifiers,
    const int &min_repeats,
    const int &max_repeats
) :
    PatternUnit(modifiers),
    child_units_(),
    min_repeats_(min_repeats),
    max_repeats_(max_repeats),
    cur_repeat_(0) {
  child_units_.push_back(std::move(pu));
}

void RepeatUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  child_units_.at(0)->Initialize(pos, max_pos, stay_at_pos);

  sequence_iterator_end_ = max_pos;
  cur_repeat_ = 0;
}

bool RepeatUnit::FindMatch() {
  // Inner loop tries to find a match with current unit and increase to the
  // next unit. If this fails, the outer loop will decrease current unit.
  for ( ; cur_repeat_ >=0; cur_repeat_-- ) {
    for ( ; cur_repeat_ <max_repeats_; cur_repeat_++ ) {
      if ( child_units_.at(cur_repeat_)->FindMatch() ) {
        // A match was found on the last of the punits. Success
        if (cur_repeat_ == max_repeats_) {
          ComposeMatches();
          return true;
        }

        // Next loop iteration will FindMatch on next current_unit_. Create it if necessary
        if (cur_repeat_ + 1 == child_units_.size()) {
          child_units_.push_back(std::move(
            std::unique_ptr<PatternUnit>(child_units_[cur_repeat_]->Clone())));
        }

        // Now initialize it
        const Match &cur_match = child_units_.at(cur_repeat_)->GetMatch();
        child_units_.at(cur_repeat_ + 1)->Initialize(
            cur_match.pos + cur_match.len,
            sequence_iterator_end_,
            true);

      } else if (cur_repeat_ >= min_repeats_) {  // min_repeats_ is reached: Great success.
        ComposeMatches();
        cur_repeat_--;
        return true;

      } else if (cur_repeat_ == 0) {  // child_units_[0] has no more matches. No more to be done.
        return false;

      } else {  // min_repeats not reached but theres hope. Break and try to decrease cur_repeat_
        break;
      }
    }
  }

  return false;
}

// Assumes its being called from FindMatch and that all entries in child_units_ from index 0 to
// cur_repeat_ have returned true to a FindMatch call.
void RepeatUnit::ComposeMatches() {
//  std::string::const_iterator match_pos = child_units_.at(0)->GetMatch().pos;
//
//  int match_length = 0; // Total length of the CompositeUnit match
//  int match_edits  = 0; // Total edits of the CompositeUnit match
//
//  int r=0;
//  for (auto &pu: child_units_) {
//    match_length += pu->GetMatch().len;
//    match_edits  += pu->GetMatch().edits;
//
//    if( ++r == cur_repeat_ )
//      break;
//  }

  if (repeat_match_) delete repeat_match_;

//  repeat_match_ = new Match( match_pos, match_length, match_edits );

  std::vector<Match> sub_matches;
  for (int r = 0; r < cur_repeat_; r++)
    sub_matches.push_back(child_units_[r]->GetMatch());

  repeat_match_ = new Match( sub_matches );
}

const Match& RepeatUnit::GetMatch() const {
  return *repeat_match_;
}

std::ostream& operator<<(std::ostream& os, const RepeatUnit& obj) {
  return obj.Print(os);
}

std::ostream& RepeatUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);

  child_units_.at(0)->Print(os);

  modifiers_.PrintPUSuffix(os);

  os << "{" << min_repeats_ << "," << max_repeats_ << "}";

  return os;
}
