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
#ifndef BACKTRACK_UNIT_H
#define BACKTRACK_UNIT_H

#include <set>
#include <vector>
#include <string>

#include "pattern_unit.h"
#include "../match.h"

class BacktrackUnit: public PatternUnit{

public:
  BacktrackUnit(const Modifiers &modifiers, const std::string& pattern);

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false
  );
  bool FindMatch();
  const Match& GetMatch();

private:
  const std::string pattern_;

  std::string::const_iterator sequence_iterator_;
  std::string::const_iterator sequence_iterator_end_;

  std::set<Match> last_found_matches_;
  int last_found_index_;

  void CollectMatches(std::string::const_iterator seq_it,
                      std::string::const_iterator pat_it,
                      const int M_left, const int I_left, const int D_left,
                      const int M_used, const int I_used, const int D_used  );
};


#endif // BACKTRACK_UNIT_H
