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
#include <string>

GroupUnit::GroupUnit(const Modifiers &modifiers, const std::string &char_group, const bool &negator):
    PatternUnit(modifiers),
    char_group_(char_group),
    negator_(negator)
{
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

bool GroupUnit::FindMatch() {
  if (negator_) {
    if (stay_at_pos_) {
      for (auto p : char_group_) {
        if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) return false;
      }
    } else {
      while (sequence_iterator_ != sequence_iterator_end_) {
        for (auto p : char_group_) {
          if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) return false;
        }

        ++sequence_iterator_;
      }
    }

    return true;
  } else {
    if (stay_at_pos_) {
      for (auto p : char_group_) {
        if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) return true;
      }
    } else {
      while (sequence_iterator_ != sequence_iterator_end_) {
        for (auto p : char_group_) {
          if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) return true;
        }

        ++sequence_iterator_;
      }
    }

    return false;
  }
}

const Match& GroupUnit::GetMatch() const {
  return std::move(Match(sequence_iterator_, 1, 0));
}
