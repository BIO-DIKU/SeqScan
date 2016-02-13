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

#include "tnfa_start_state_indel.h"

TNFAStartStateIndel::TNFAStartStateIndel(uint64_t e) : TNFAStateIndel(0),
                                                       stateErrorCode_(e) {}

void TNFAStartStateIndel::addEpsilonTransitions(
    bool listNo,
    std::string::const_iterator pos,
    std::vector< TNFAStateIndel * > stateLists[],
    std::unordered_map<int, int> &matchMap,
    uint32_t listID)
{
  out_->addToList(stateErrorCode_, listNo, pos, stateLists, matchMap, listID);
}

void TNFAStartStateIndel::addOutStates(bool listNo,
                                       std::string::const_iterator pos,
                                       std::vector< TNFAStateIndel * > stateLists[],
                                       std::unordered_map<int, int> &matchMap,
                                       uint32_t listID)
{
  if (indels(errorCode_[!listNo]))
    addToList(
        decrementIndels(errorCode_[!listNo]),
        listNo,
        pos,
        stateLists,
        matchMap,
        listID
    );
}

void TNFAStartStateIndel::display(bool) {
  printf("StartState %p points to %p with error code %lu\n",
    (void *) this, (void *) out_, stateErrorCode_);
}
