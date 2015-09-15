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

#ifndef PU_TNFA_START_STATE_H_
#define PU_TNFA_START_STATE_H_

#include <inttypes.h>
#include <string>
#include <vector>

#include "tnfa_state.h"

using std::map;

class TNFAStartState : public TNFAState {
 public:
  TNFAStartState(uint64_t[8]);

  void addEpsilonTransitions(bool, std::string::const_iterator,
                             std::vector< TNFAState * > [],
                             std::map<int, int> &,
                             uint32_t);

  void addOutStates(bool, std::string::const_iterator,
                    std::vector< TNFAState * > [],
                    std::map<int, int> &,
                    uint32_t);

  void display(bool);

 private:

  uint64_t stateErrorCode_[ 8 ];
};

TNFAStartState::TNFAStartState(uint64_t e[8]) : TNFAState(0) {
  for (int i = 0; i < 8; i++)
    stateErrorCode_[ i ] = e[ i ];
}

void TNFAStartState::addEpsilonTransitions(
    bool listNo,
    std::string::const_iterator pos,
    std::vector< TNFAState * > stateLists[],
    std::map<int, int> &matchMap,
    uint32_t listID)
{
  out_->addToList(stateErrorCode_, listNo, pos, stateLists, matchMap, listID);
}

void TNFAStartState::addOutStates(bool listNo,
                                  std::string::const_iterator pos,
                                  std::vector< TNFAState * > stateLists[],
                                  std::map<int, int> &matchMap,
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

void TNFAStartState::display(bool) {
  printf("StartState %p points to %p with error code %llu\n",
    (void *) this, (void *) out_, stateErrorCode_[0]);
}


#endif  // PU_LEVENSHTEIN_STATE_H_
