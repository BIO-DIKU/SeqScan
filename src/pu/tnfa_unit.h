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

#ifndef PU_TNFA_UNIT_H_
#define PU_TNFA_UNIT_H_

#include <string>
#include <vector>
#include <map>

#include "pattern_unit.h"
#include "tnfa_state.h"

using std::string;

class TNFAUnit : public PatternUnit {
 public:
  TNFAUnit(const Modifiers &modifiers, const string& pattern);

  void Initialize(string::const_iterator pos,
                  string::const_iterator max_pos,
                  bool stay_at_pos = false);
  bool FindMatch();
  const Match& GetMatch();
  // Create error codes from m,i,d modifiers
  void ModifiersToErrorCode(const Modifiers &modifiers);

 private:
  const string           pattern_;
  string::const_iterator sequence_iterator_;
  string::const_iterator sequence_iterator_end_;
  bool                   stay_at_pos_;
  TNFAState              *startState_;
  uint64_t               errorCode_[8];
  vector< TNFAState * >  stateLists_[ 2 ];
  bool                   listNo_;
  vector< Match >        matches;
  uint32_t               listID_;
  std::map< int, int >   matchMap_;
};

#endif  // PU_TNFA_UNIT_H_
