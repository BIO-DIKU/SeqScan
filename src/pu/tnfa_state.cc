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

#include "tnfa_state.h"

#include <iostream>
#include <functional>
#include <string>

using ::std::vector;
using ::std::unordered_map;

uint64_t TNFAState::newCode[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

TNFAState::TNFAState(char cInit) : c(cInit) {}

void TNFAState::setOutPtr(TNFAState *out) { out_ = out; }
TNFAState *TNFAState::getOutPtr() { return out_; }

void TNFAState::addToList(uint64_t e[8],
                          bool listNo,
                          std::string::const_iterator pos,
                          vector< TNFAState * > stateLists[2],
                          unordered_map<int, int> &matchMap, uint32_t listID)
{
  if (listID_ != listID) {
    listID_ = listID;

    //memcpy(errorCode_[listNo], e, sizeof(uint64_t)*8);
    for (int i = 0; i < 8; i++)
      errorCode_[listNo][i] = e[i];

    addEpsilonTransitions(listNo, pos, stateLists, matchMap, listID);
    stateLists[listNo].push_back(this);

  } else if (
      (errorCode_[listNo][0] | e[0]) != errorCode_[listNo][0] ||
      (errorCode_[listNo][1] | e[1]) != errorCode_[listNo][1] ||
      (errorCode_[listNo][2] | e[2]) != errorCode_[listNo][2] ||
      (errorCode_[listNo][3] | e[3]) != errorCode_[listNo][3] ||
      (errorCode_[listNo][4] | e[4]) != errorCode_[listNo][4] ||
      (errorCode_[listNo][5] | e[5]) != errorCode_[listNo][5] ||
      (errorCode_[listNo][6] | e[6]) != errorCode_[listNo][6] ||
      (errorCode_[listNo][7] | e[7]) != errorCode_[listNo][7] )
  {
    /* The union of two error subsets corresponds to the alternation of the
     * error codes.
     */
    for ( int i = 0; i < 8; i++ )
      errorCode_[listNo][i] |= e[i];

    addEpsilonTransitions(listNo, pos, stateLists, matchMap, listID);
  }
}

void TNFAState::addEpsilonTransitions(bool listNo,
                                      std::string::const_iterator pos,
                                      vector< TNFAState * > stateLists[],
                                      unordered_map<int, int> &matchMap,
                                      uint32_t listID) {
  // Handle deletions
  if (deletions(errorCode_[listNo])) {
    out_->addToList(decrementDeletions(errorCode_[listNo]), listNo,
                    pos, stateLists, matchMap, listID);
  }
}

void TNFAState::addOutStates(bool listNo, std::string::const_iterator pos,
                             vector< TNFAState * > stateLists[],
                             unordered_map<int, int> &matchMap, uint32_t listID) {
  // TODO(Sune): Handle lower/upper case with modifiers
  if (*pos == c) {
    out_->addToList(errorCode_[ !listNo ], listNo, pos, stateLists, matchMap, listID);
  } else {
    // Handle mismatches
    if (mismatches(errorCode_[!listNo]))
      out_->addToList(decrementMismatches(errorCode_[!listNo]),
                      listNo, pos, stateLists, matchMap, listID);
    // Handle insertions
    if (insertions(errorCode_[!listNo]))
      addToList(decrementInsertions(errorCode_[!listNo]), listNo,
                pos, stateLists, matchMap, listID);
  }
}

void TNFAState::display(bool listNo) {
  printf("TNFAState %p on %c points to %p with errorcode %llu\n", (void *) this,
         c, (void *) out_, errorCode_[!listNo][0]);
}

bool TNFAState::mismatches(uint64_t eCode[8]) {
  return eCode[0] & 2;
}

bool TNFAState::deletions(uint64_t eCode[8]) {
  return eCode[ 0 ] & 0x100;
}

bool TNFAState::insertions(uint64_t eCode[8]) {
  return eCode[ 1 ] & 1;
}

uint64_t *TNFAState::decrementMismatches(uint64_t eCode[8]) {
  for (int i = 0; i < 8; i++ )
    newCode[i] = (eCode[i] & 0xFEFEFEFEFEFEFEFE) >> 1;

  return newCode;
}

uint64_t *TNFAState::decrementDeletions(uint64_t eCode[8]) {
  for (int i = 0; i < 8; i++)
    newCode[i] = (eCode[i] & 0xFFFFFFFFFFFFFF00) >> 8;

  return newCode;
}

uint64_t *TNFAState::decrementInsertions(uint64_t eCode[8]) {
  for (int i = 0; i < 7; i++ )
    newCode[i] = eCode[ i + 1 ];

  newCode[7] = 0;

  return newCode;
}
