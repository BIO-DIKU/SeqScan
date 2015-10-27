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

#ifndef SEQSCAN_PU_RANGE_UNIT_H_
#define SEQSCAN_PU_RANGE_UNIT_H_

#include <iostream>
#include <vector>

#include "pattern_unit.h"
#include "../match.h"

class RangeUnit : public PatternUnit {
public:
  /** Construct a RangeUnit with the specified modifiers and min-to-max length. */
  RangeUnit(const Modifiers &modifiers, const int min_length, const int max_length);

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false) override;

  bool FindMatch() override;

  const Match& GetMatch() const override;

  std::ostream& Print(std::ostream &os) const override;

  std::unique_ptr<PatternUnit> Clone() const override;

private:
  std::string::const_iterator start_pos_;
  std::string::const_iterator end_pos_;
  bool stay_at_pos_;

  const unsigned int min_length_;
  const unsigned int max_length_;

  std::vector< Match > matches_;
  size_t cur_match_;
};


#endif  // SEQSCAN_PU_RANGE_UNIT_H_
