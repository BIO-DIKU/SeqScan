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

#include "tnfa_start_state_64.h"

TNFAStartState64::TNFAStartState64(uint64_t e) : TNFAState64(0), stateErrorCode_(e) {}

void TNFAStartState64::addEpsilonTransitions(
    bool listNo,
    std::string::const_iterator pos,
    std::vector< TNFAState64 * > stateLists[],
    std::unordered_map<int, int> &matchMap,
    uint32_t listID)
{
  out_->addToList(stateErrorCode_, listNo, pos, stateLists, matchMap, listID);
}

void TNFAStartState64::addOutStates(bool listNo,
                                  std::string::const_iterator pos,
                                  std::vector< TNFAState64 * > stateLists[],
                                  std::unordered_map<int, int> &matchMap,
                                  uint32_t listID)
{
  if (insertions(errorCode_[!listNo]))
    addToList(
        decrementInsertions(errorCode_[!listNo]),
        listNo,
        pos,
        stateLists,
        matchMap,
        listID
    );
}

void TNFAStartState64::display(bool) {
  printf("StartState %p points to %p with error code %llu\n",
    (void *) this, (void *) out_, stateErrorCode_);
}
