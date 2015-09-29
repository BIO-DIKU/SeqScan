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

#include "range_unit.h"

#include <algorithm>

RangeUnit::RangeUnit(const Modifiers &modifiers, const int min_length, const int max_length):
    PatternUnit(modifiers),
    min_length_(min_length),
    max_length_(max_length)
{}

void RangeUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos) {
  start_pos_    = pos;
  end_pos_      = max_pos;
  stay_at_pos_  = stay_at_pos;

  cur_match_    = -1;
  matches_.clear();
  int chars_remaining = end_pos_ - start_pos_;
  for (int l = min_length_; l <= std::min((int)max_length_, chars_remaining - 1); l++) {
    matches_.push_back(Match(start_pos_, l, 0));
  }
}

bool RangeUnit::FindMatch() {
  cur_match_++;

  if (cur_match_ >= matches_.size()) {
    if (stay_at_pos_) return false;

    start_pos_++;
    int chars_remaining = end_pos_ - start_pos_;
    matches_.clear();

    for (int l = min_length_; l <= std::min((int)max_length_, chars_remaining - 1); l++) {
      matches_.push_back(Match(start_pos_, l, 0));
    }

    cur_match_ = 0;
  }

  return !matches_.empty();
}

const Match& RangeUnit::GetMatch() const {
  return matches_[cur_match_];
}

std::ostream& RangeUnit::Print(std::ostream &os) const {
  modifiers_.PrintPUPrefix(os);

  return os << min_length_ << ".." << max_length_;
}

std::unique_ptr<PatternUnit> RangeUnit::Clone() const {
  std::unique_ptr<PatternUnit> ret =
      std::unique_ptr<PatternUnit>(
          new RangeUnit(modifiers_,
                        min_length_,
                        max_length_));

  return ret;
}
