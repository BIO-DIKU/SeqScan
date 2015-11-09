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

#include "group_unit.h"

GroupUnit::GroupUnit(const Modifiers &modifiers, const std::string& pattern, const bool& negator):
    PatternUnit(modifiers),
    pattern_(pattern),
    negator_(negator)
{
    std::cerr << "pattern: " << pattern << std::endl;
    std::cerr << "negator: " << negator << std::endl;
}

void GroupUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
) {
  sequence_iterator_     = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_           = stay_at_pos;
}

void GroupUnit::ResMatcherCoerce() {
  modifiers_.res_matcher_;
}

bool GroupUnit::FindMatch() {
  while (sequence_iterator_ != sequence_iterator_end_) {
    for (auto p : pattern_) {
      if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) return true;
    }
  }

  return false;
}

const Match& GroupUnit::GetMatch() const {
  // std::set<Match >::iterator it = last_found_matches_.begin();
  // std::advance(it, last_found_index_);
  // return *it;
}
