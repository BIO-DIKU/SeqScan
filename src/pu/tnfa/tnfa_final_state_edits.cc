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

#include "tnfa_final_state_edits.h"

using ::std::string;
using ::std::vector;
using ::std::unordered_map;

TNFAFinalStateEdits::TNFAFinalStateEdits(int len, int edits)
  : TNFAStateEdits(0), patternLength_(len), maxEdits_(edits) {}

void TNFAFinalStateEdits::addOutStates(bool,
                                       string::const_iterator,
                                       vector< TNFAStateEdits * > [],
                                       unordered_map<int, int> &,
                                       uint32_t) {}

void TNFAFinalStateEdits::addEpsilonTransitions(bool listNo,
                                                string::const_iterator,
                                                vector< TNFAStateEdits * >[],
                                                unordered_map<int, int> &matchMap,
                                                uint32_t)
{
  // Find length and number of used edits for all matches
  int                matchLength = 0;
  int                editsLeft   = 0;

  //TODO (Sune): Find another way to compute match lengths
  matchLength = patternLength_;// + counterToDeletions(c) - counterToInsertions(c);
  editsLeft = errorCode_[listNo];
  if (matchMap.count(matchLength) == 0
      || matchMap[matchLength] > maxEdits_ - editsLeft)
    matchMap[matchLength] = maxEdits_ - editsLeft;
}
