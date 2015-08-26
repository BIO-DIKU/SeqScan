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
#ifndef TNFA_SEQUENCE_UNIT_H
#define TNFA_SEQUENCE_UNIT_H

#include "pattern_unit.h"
#include "tnfa_state.h"

class TNFASequenceUnit: public PatternUnit {
 public:
  TNFASequenceUnit(const Modifiers &modifiers, const std::string& pattern);

  void Initialize(std::string::const_iterator pos,
                  std::string::const_iterator max_pos);
  bool HasNextMatch();
  //TODO: Implement
  Match& NextMatch() { return matches.back(); };
  void ModifiersToErrorCode(const Modifiers &modifiers);

 private:
  const std::string pattern_;

  std::string::const_iterator sequence_iterator_;
  std::string::const_iterator sequence_iterator_end_;
  TNFAState *startState_;
  uint64_t errorCode_[8];
  vector< TNFAState * > stateLists_[ 2 ];
  bool listNo_;
  vector< Match > matches;
  uint32_t listID_;
};


#endif // TNFA_SEQUENCE_UNIT_H
