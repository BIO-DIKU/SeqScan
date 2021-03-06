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

#ifndef SEQSCAN_PU_TNFA_UNIT_H_
#define SEQSCAN_PU_TNFA_UNIT_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "../pattern_unit.h"
#include "tnfa_model.h"

class TNFAUnit : public PatternUnit {
public:

  TNFAUnit(const Modifiers &modifiers, const std::string);

  void Initialize(std::string::const_iterator pos,
                  std::string::const_iterator max_pos,
                  bool stay_at_pos = false);

  bool FindMatch();

  const Match& GetMatch() const;

  std::ostream& Print(std::ostream &os) const;
private:
  TNFAModel         *model_;
  const std::string pattern_;
};

#endif   // SEQSCAN_PU_TNFA_UNIT_H_

