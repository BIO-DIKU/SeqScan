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

#include "composite_unit.h"   // TODO(Rasmus): include directory when naming .h files


CompositeUnit::CompositeUnit(const Modifiers &modifiers) :
    PatternUnit(modifiers),
    composite_match_(0)
{}

void CompositeUnit::AddUnit(std::unique_ptr<PatternUnit> &unit) {
  punits_.push_back(std::move(unit));
}

void CompositeUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;

  punits_.at(0)->Initialize(pos, max_pos, stay_at_pos);
  current_unit_ = 0;
}

void CompositeUnit::ComposeMatches() {
  std::string::const_iterator match_pos = punits_.at(0)->GetMatch().pos;

  int match_length = 0;
  int match_edits  = 0;
  for (auto &pu : punits_) {
    match_length += pu->GetMatch().len;
    match_edits  += pu->GetMatch().edits;
  }

  if (composite_match_) delete composite_match_;
  composite_match_ = new Match( match_pos, match_length, match_edits );
}

bool CompositeUnit::FindMatch() {
  size_t n = punits_.size();

  // Inner loop tries to find a match with current unit and increase to the
  // next unit. If this fails, the outer loop will decrease current unit.
  for ( ; current_unit_ >= 0; current_unit_--) {
    for ( ; current_unit_ < n; current_unit_++) {
      if (punits_.at(current_unit_)->FindMatch()) {
        // A match was found on the last of the punits. Success
        if (current_unit_ == n - 1) {
          ComposeMatches();
          return true;
        }

        // Next loop iteration will FindMatch on next current_unit_. Initialize
        // it.
        const Match& cur_match = punits_.at(current_unit_)->GetMatch();
        punits_.at(current_unit_ + 1)->Initialize(cur_match.pos + cur_match.len,
                                                  sequence_iterator_end_, true);
      } else {   // No more matches at current_unit_. Break loop and decrease
        break;
      }
    }
  }

  return false;
}

const Match& CompositeUnit::GetMatch() {
  return *composite_match_;
}

std::ostream& operator<<(std::ostream& os, const CompositeUnit& obj) {
  return obj.print(os);
}

std::ostream& CompositeUnit::print(std::ostream& os) const {
  for (size_t i = 0; i < punits_.size() - 1; i++) {
    punits_.at(i)->print(os) << " ";
  }

  punits_.back()->print(os);

  return os;
}
