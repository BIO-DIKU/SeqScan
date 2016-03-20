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
#include <assert.h>

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
  assert (pos!=max_pos);

  sequence_iterator_     = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_           = stay_at_pos;
  pos_was_checked_       = false;
}

bool GroupUnit::FindMatch() {
  if (stay_at_pos_) {
    return negator_ ? FindNoMatchAtPos() : FindMatchAtPos();
  } else {
    return negator_ ? FindNoMatchIter() : FindMatchIter();
  }
}

bool GroupUnit::FindNoMatchAtPos() {
  if (pos_was_checked_) return false;

  bool match = false;

  for (auto p : char_group_) {
    if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
      match = true;
      break;
    }
  }

  pos_was_checked_ = true;

  if (!match) {
    UpdateMatch();
    return true;
  }

  return false;
}

bool GroupUnit::FindMatchAtPos() {
  if (pos_was_checked_) return false;

  for (auto p : char_group_) {
    if (modifiers_.res_matcher_.Match(*sequence_iterator_, p)) {
      UpdateMatch();
      pos_was_checked_ = true;
      return true;
    }
  }

  pos_was_checked_ = true;
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

inline void GroupUnit::UpdateMatch() {
  if (match_ != NULL) delete match_;
  match_ = new Match(sequence_iterator_, 1, 0);
  ++sequence_iterator_;
}

std::unique_ptr<PatternUnit> GroupUnit::Clone() const {
  std::unique_ptr<PatternUnit> ret( new GroupUnit(modifiers_, char_group_, negator_) );
  return std::move(ret);
}
