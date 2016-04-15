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

#ifndef SEQSCAN_PU_REFERENCE_UNIT_H_
#define SEQSCAN_PU_REFERENCE_UNIT_H_

#include "pattern_unit.h"

class ReferenceUnit : public PatternUnit{
public:
  ReferenceUnit(
      PatternUnit* pu,
      const Modifiers &modifiers
  );

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false
  ) override;

  bool FindMatch() override;

  const Match& GetMatch() const override;

  std::ostream& Print(std::ostream &os) const override;

  std::unique_ptr<PatternUnit> Clone() const override;

private:

  std::string ref_match_;

  std::string::const_iterator sequence_iterator_end_;

  PatternUnit* referenced_unit_;

  std::unique_ptr<PatternUnit> pattern_finder_;
};


#endif  // SEQSCAN_PU_REFERENCE_UNIT_H_
