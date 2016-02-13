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

#include "tnfa_state_edits.h"

#include <iostream>
#include <functional>
#include <string>

using ::std::vector;
using ::std::unordered_map;

TNFAStateEdits::TNFAStateEdits(char cInit) : c(cInit) {}

void TNFAStateEdits::setOutPtr(TNFAStateEdits *out) { out_ = out; }
TNFAStateEdits *TNFAStateEdits::getOutPtr() { return out_; }

void TNFAStateEdits::addToList(uint64_t e,
                               bool listNo,
                               std::string::const_iterator pos,
                               vector< TNFAStateEdits * > stateLists[2],
                               unordered_map<int, int> &matchMap, uint32_t listID)
{
  if (listID_ != listID) {
    listID_ = listID;


    errorCode_[listNo] = e;

    addEpsilonTransitions(listNo, pos, stateLists, matchMap, listID);
    stateLists[listNo].push_back(this);

  } else if ((errorCode_[listNo] | e) != errorCode_[listNo])
  {
    /* The union of two error subsets corresponds to the alternation of the
     * error codes.
     */
    errorCode_[listNo] |= e;

    addEpsilonTransitions(listNo, pos, stateLists, matchMap, listID);
  }
}

void TNFAStateEdits::addEpsilonTransitions(bool listNo,
                                           std::string::const_iterator pos,
                                           vector< TNFAStateEdits * > stateLists[],
                                           unordered_map<int, int> &matchMap,
                                           uint32_t listID) {
  // Handle deletions
  if (errorCode_[listNo]) {
    out_->addToList(errorCode_[listNo] - 1, listNo,
                    pos, stateLists, matchMap, listID);
  }
}

void TNFAStateEdits::addOutStates(bool listNo, std::string::const_iterator pos,
                                  vector< TNFAStateEdits * > stateLists[],
                                  unordered_map<int, int> &matchMap, uint32_t listID) {
  // TODO(Sune): Handle lower/upper case with modifiers
  if (*pos == c) {
    out_->addToList(errorCode_[ !listNo ], listNo, pos, stateLists, matchMap, listID);
  } else {
    if (errorCode_[!listNo]) {
      // Handle mismatches
      out_->addToList(errorCode_[!listNo] - 1,
                      listNo, pos, stateLists, matchMap, listID);
      // Handle insertions
      addToList(errorCode_[!listNo] - 1, listNo, pos, stateLists, matchMap, listID);
    }
  }
}

void TNFAStateEdits::display(bool listNo) {
  printf("TNFAState64 %p on %c points to %p with errorcode %lu\n", (void *) this,
         c, (void *) out_, errorCode_[!listNo]);
}
