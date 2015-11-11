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

#ifndef SEQSCAN_GROUP_UNIT_H_
#define SEQSCAN_GROUP_UNIT_H_

#include "pattern_unit.h"
#include "res_matcher.h"

/**
 * Pattern unit for matching a group of specified residues e.g. [ATC] with the
 * option of also negating the matching e.g. [^ATC].
 */
class GroupUnit : public PatternUnit {
 public:
  GroupUnit(const Modifiers &modifiers, const std::string &char_group, const bool &negator);

  void Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos = false) override;

  virtual bool FindMatch() override;

  const Match& GetMatch() const override;

 protected:
  const std::string char_group_;
  const bool        negator_;

  /** The start sequence iterator. */
  std::string::const_iterator sequence_iterator_;

  /** The end sequence iterator. */
  std::string::const_iterator sequence_iterator_end_;

  /** Indicates whether FindMatch should search for matches starting at other positions than the
   * one indicated in Initialize */
  bool stay_at_pos_;
};

#endif  // SEQSCAN_GROUP_UNIT_H_
