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
  negator_(negator),
  match_(NULL)
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
  if (stay_at_pos_) {
    if (negator_) {
      return FindNoMatchAtPos();
    } else {
      return FindMatchAtPos();
    }
  } else {
    if (negator_) {
      return FindNoMatchIter();
    } else {
      return FindMatchIter();
    }
  }
}

bool GroupUnit::FindNoMatchAtPos() {
  bool match = false;

  for (auto p : char_group_) {
    if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
      match = true;
      break;
    }
  }

  if (!match) {
    UpdateMatch();
    return true;
  }

  return false;
}

bool GroupUnit::FindMatchAtPos() {
  for (auto p : char_group_) {
    if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
      UpdateMatch();
      return true;
    }
  }

  return false;
}

bool GroupUnit::FindNoMatchIter() {
  while (sequence_iterator_ != sequence_iterator_end_) {
    bool match = false;

    for (auto p : char_group_) {
      if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
        match = true;
        break;
      }
    }

    if (!match) {
      UpdateMatch();
      return true;
    }

    ++sequence_iterator_;
  }

  return false;
}

bool GroupUnit::FindMatchIter() {
  while (sequence_iterator_ != sequence_iterator_end_) {
    for (auto p : char_group_) {
      if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
        UpdateMatch();
        return true;
      }
    }

    ++sequence_iterator_;
  }

  return false;
}

const Match& GroupUnit::GetMatch() const {
  return *match_;
}
