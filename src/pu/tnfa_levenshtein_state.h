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

#ifndef PU_LEVENSHTEIN_STATE_H_
#define PU_LEVENSHTEIN_STATE_H_

#include <inttypes.h>
#include <string>
#include <vector>

#include "tnfa_state.h"

class TNFALevenshteinState : public TNFAState {
 public:
  TNFALevenshteinState(uint64_t[8]);
  void addEpsilonTransitions(bool, std::string::const_iterator,
                             vector< TNFAState * > [], vector< Match > &,
                             uint32_t);
  void addOutStates(bool, std::string::const_iterator, vector< TNFAState * > [],
                    vector< Match > &, uint32_t);
  void display(bool);
 private:
  uint64_t stateErrorCode_[ 8 ];
};

TNFALevenshteinState::TNFALevenshteinState(uint64_t e[8]) : TNFAState(0) {
  for (int i = 0; i < 8; i++)
    stateErrorCode_[ i ] = e[ i ];
}

void TNFALevenshteinState::addEpsilonTransitions(
    bool listNo, std::string::const_iterator pos, vector< TNFAState * > stateLists[],
    vector< Match > &matches, uint32_t listID) {
  out_->addToList(stateErrorCode_, pathTag, listNo, pos, stateLists, matches, listID);
}

void TNFALevenshteinState::addOutStates(bool listNo,
                                        std::string::const_iterator pos,
                                        vector< TNFAState * > stateLists[],
                                        vector< Match > &matches,
                                        uint32_t listID) {
  if (insertions(errorCode_[!listNo]))
    addToList(decrementInsertions(errorCode_[!listNo]), pathTag, listNo, pos,
              stateLists, matches, listID);
}

void TNFALevenshteinState::display(bool) {
  printf("LevenshteinState %p points to %p with error code %llu\n",
    (void *) this, (void *) out_, stateErrorCode_[0]);
}


#endif  // PU_LEVENSHTEIN_STATE_H_
