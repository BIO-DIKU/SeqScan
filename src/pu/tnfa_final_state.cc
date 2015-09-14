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

#include "tnfa_final_state.h"

#include <map>

TNFAFinalState::TNFAFinalState(int len, int edits)
  : TNFAState(0), patternLength_(len), maxEdits_(edits) {}

void TNFAFinalState::addOutStates(bool listNo, std::string::const_iterator pos,
                                  vector< TNFAState * > stateLists[],
                                  vector< Match > &matches, uint32_t listID) {
  if (insertions(errorCode_[!listNo]))
    addToList(decrementInsertions(errorCode_[!listNo]), listNo,
              pos, stateLists, matches, listID);
}

void TNFAFinalState::addEpsilonTransitions(bool listNo,
                                           std::string::const_iterator pos,
                                           vector< TNFAState * > stateLists[],
                                           vector< Match > &matches,
                                           uint32_t listID) {
  // Find length and number of used edits for all matches
  std::map<int, int> matchMap;  // TODO(Sune): should be intialized somehow
  int                matchLength = 0;
  int                editsLeft   = 0;

  // FIXME(Sune): suggestion: replace magic numbers (511, 0x38 etc) with
  // constants. Possibly also replace cryptic statements such as
  // (uint64_t) 1 << c % 64) with inline functions or macros (the latter seems
  // to be discuraged because of scope issues). The inline function name will
  // improve understanding of the code ala:
  //   inline bool bit_is_set(int c, ...) {...}
  for (int c = 511; c >= 0; c--) {
    if (errorCode_[listNo][c / 64] & (uint64_t) 1 << c % 64) {
      // matchLength = patternLength + unused deletions - unused insertions
      matchLength = patternLength_ + (c & 0x38) / 8 - (c & 0x1C0) / 64;
      editsLeft = (c & 7) + (c & 0x38) / 8 + (c & 0x1C0) / 64;
      if (matchMap.count(matchLength) == 0 || matchMap[matchLength] < editsLeft)
        matchMap[matchLength] = editsLeft;
    }
  }

  for (auto matchPair : matchMap)
    matches.push_back(Match(pos - matchPair.first + 1, matchPair.first,
                            maxEdits_ - matchPair.second));
}
