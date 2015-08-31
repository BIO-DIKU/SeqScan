
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

extern bool showAllMatches;

TNFAFinalState::TNFAFinalState(int len, int edits)
  : TNFAState(0), patternLength_(len), maxEdits_(edits) {}

void TNFAFinalState::addOutStates(bool listNo, std::string::const_iterator pos,
                                  vector< TNFAState * > stateLists[],
                                  vector< Match > &matches, uint32_t listID) {
  if (insertions(errorCode_[!listNo]))
    addToList(decrementInsertions(errorCode_[!listNo]), pathTag, listNo,
              pos, stateLists, matches, listID);
}

void TNFAFinalState::addEpsilonTransitions(bool listNo,
                                           std::string::const_iterator pos,
                                           vector< TNFAState * > stateLists[],
                                           vector< Match > &matches,
                                           uint32_t listID) {
  // Find length and number of used edits for all matches
  std::set<pair<int, int>> matchPairs;
  for (int c = 511; c >= 0; c--)
    if (errorCode_[listNo][c / 64] & (uint64_t) 1 << c % 64)
      matchPairs.insert( pair<int, int>((c & 0x38) / 8 - (c & 0x1C0) / 64,
                                        (c & 7) + (c & 0x38) / 8 + (c & 0x1C0) / 64));
  for (auto matchPair : matchPairs) {
    matches.push_back(Match(pos - patternLength_ + 1,
                            patternLength_ + matchPair.first,
                            maxEdits_ - matchPair.second));
  }
}
