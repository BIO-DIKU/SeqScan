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

#include <assert.h>
#include "composite_unit.h"   // TODO(Rasmus): include directory when naming .h files


CompositeUnit::CompositeUnit(const Modifiers &modifiers) :
    PatternUnit(modifiers),
    composite_match_(0)
{}

void CompositeUnit::AddUnit(std::unique_ptr<PatternUnit> &unit) {
  child_units_.push_back(std::move(unit));
}

void CompositeUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  assert (pos!=max_pos);

  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;

  child_units_.at(0)->Initialize(pos, max_pos, stay_at_pos);
  current_unit_ = 0;
}

// Assumes its being called from FindMatch and that all entries in child_units_ has returned true
// to a FindMatch call.
void CompositeUnit::ComposeMatches() {
  // std::string::const_iterator match_pos = child_units_.at(0)->GetMatch().pos;

  // int match_length = 0; // Total length of the CompositeUnit match
  // int match_edits  = 0; // Total edits of the CompositeUnit match
  //
  // for (auto &pu: child_units_) {
  //  match_length += pu->GetMatch().len;
  //  match_edits  += pu->GetMatch().edits;
  // }

  if (composite_match_) delete composite_match_;

  // composite_match_ = new Match( match_pos, match_length, match_edits );

  std::vector<Match> sub_matches;
  for (auto &pu : child_units_)
    sub_matches.push_back(pu->GetMatch());

  composite_match_ = new Match( sub_matches );
}

bool CompositeUnit::FindMatch() {
  size_t n = child_units_.size();

  // Inner loop tries to find a match with current unit and increase to the
  // next unit. If this fails, the outer loop will decrease current unit.
  for ( ; ; current_unit_-- ) {
    for ( ; current_unit_ < n; current_unit_++) {
      if ( child_units_.at(current_unit_)->FindMatch() ) {
        // A match was found on the last of the punits. Success
        if (current_unit_ == n - 1) {
          ComposeMatches();
          return true;
        }

        const Match &cur_match = child_units_.at(current_unit_)->GetMatch();
        // The end of the sequence has been reached. Stop searching.
        if ((sequence_iterator_end_ - cur_match.pos) - cur_match.len <= 0)
          return false;

        // Next loop iteration will FindMatch on next current_unit_. Initialize it
        child_units_.at(current_unit_ + 1)->Initialize(
            cur_match.pos + cur_match.len,
            sequence_iterator_end_,
            true);

      } else if (current_unit_ == 0) {
        // child_units_[0] has no more matches. We're done.
        return false;
      } else {
        // No more matches at current_unit_. Break loop and decrease
        break;
      }
    }
  }

}

const Match& CompositeUnit::GetMatch() const {
  return *composite_match_;
}

std::ostream& operator<<(std::ostream& os, const CompositeUnit& obj) {
  return obj.Print(os);
}

std::ostream& CompositeUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);

  os << "(";

  for (size_t i = 0; i < child_units_.size() - 1; i++) {
    child_units_.at(i)->Print(os) << " ";
  }

  child_units_.back()->Print(os);

  os << ")";
  modifiers_.PrintPUSuffix(os);

  return os;
}


std::unique_ptr<PatternUnit> CompositeUnit::Clone() const {
  std::unique_ptr<PatternUnit> ret = std::unique_ptr<PatternUnit>(new CompositeUnit(modifiers_));

  for (auto& cu : child_units_) {
    std::unique_ptr<PatternUnit> clone = cu->Clone();
    ((CompositeUnit *) ret.get())->AddUnit(clone);
  }

  return ret;
}
