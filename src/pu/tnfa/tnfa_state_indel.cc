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

#include "tnfa_state_indel.h"

#include <iostream>
#include <functional>
#include <string>

using ::std::vector;
using ::std::unordered_map;

TNFAStateIndel::TNFAStateIndel(char cInit) : c(cInit) {}

void TNFAStateIndel::setOutPtr(TNFAStateIndel *out) { out_ = out; }
TNFAStateIndel *TNFAStateIndel::getOutPtr() { return out_; }

void TNFAStateIndel::addToList(uint64_t e,
                               bool listNo,
                               std::string::const_iterator pos,
                               vector< TNFAStateIndel * > stateLists[2],
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

void TNFAStateIndel::addEpsilonTransitions(bool listNo,
                                           std::string::const_iterator pos,
                                           vector< TNFAStateIndel * > stateLists[],
                                           unordered_map<int, int> &matchMap,
                                           uint32_t listID) {
  // Handle deletions
  if (indels(errorCode_[listNo])) {
    out_->addToList(decrementIndels(errorCode_[listNo]), listNo,
                    pos, stateLists, matchMap, listID);
  }
}

void TNFAStateIndel::addOutStates(bool listNo, std::string::const_iterator pos,
                                  vector< TNFAStateIndel * > stateLists[],
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
    if (indels(errorCode_[!listNo]))
      addToList(decrementIndels(errorCode_[!listNo]), listNo,
                pos, stateLists, matchMap, listID);
  }
}

void TNFAStateIndel::display(bool listNo) {
  printf("TNFAState64 %p on %c points to %p with errorcode %lu\n", (void *) this,
         c, (void *) out_, errorCode_[!listNo]);
}

bool TNFAStateIndel::mismatches(uint64_t eCode) {
  return eCode & 2;
}

bool TNFAStateIndel::indels(uint64_t eCode) {
  return eCode & 0x100;
}

uint64_t TNFAStateIndel::decrementMismatches(uint64_t eCode ) {
  return ( ( eCode & 0xFEFEFEFEFEFEFEFE ) >> 1 );
}

uint64_t TNFAStateIndel::decrementIndels(uint64_t eCode) {
  return ( ( eCode & 0xFFFFFFFFFFFFFF00 ) >> 8 );
}
