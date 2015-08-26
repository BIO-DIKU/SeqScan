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
 
#include "tnfa_sequence_unit.h"
#include "tnfa_levenshtein_state.h"
#include "tnfa_final_state.h"
#include <iostream>

using namespace std;

TNFASequenceUnit::TNFASequenceUnit(const Modifiers &modifiers,
                                   const std::string& pattern) :
  PatternUnit(modifiers), pattern_(pattern), startState_( nullptr ),
  errorCode_{ 0, 0, 0, 0, 0, 0, 0, 0 } {
  TNFAState *currentState;
  ModifiersToErrorCode(modifiers);
  startState_ = currentState = new TNFALevenshteinState( errorCode_ );
  for (char c : pattern_ ) {
    currentState->setOutPtr(new TNFAState( c ));
    currentState = currentState->getOutPtr();
  }
  currentState->setOutPtr(new TNFAFinalState(pattern.length()));
}

void TNFASequenceUnit::Initialize(std::string::const_iterator pos,
                                  std::string::const_iterator max_pos) {
  sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
  listID_=0;
}

bool TNFASequenceUnit::HasNextMatch() {
  if(!matches.empty()) {
    matches.pop_back();
    if(!matches.empty())
      return true;
  }
  for(; sequence_iterator_ != sequence_iterator_end_; sequence_iterator_++) {
    stateLists_[listNo_ = ++listID_ % 2].clear();
    startState_->addToList(TNFAState::newCode, listID_, listNo_, sequence_iterator_,
                           stateLists_, matches, listID_);
    for(TNFAState *s : stateLists_[!listNo_])
      s->addOutStates(listNo_, sequence_iterator_, stateLists_, matches,
                      listID_);
    if(!matches.empty())
      return true;
  }
  return false;
}

void TNFASequenceUnit::ModifiersToErrorCode(const Modifiers &modifiers) {
  for (int c = 1; c < 512; c++) {
    if ((c & 7) <= modifiers.mismatches_
        && (c & 0x38) / 8 <= modifiers.deletions_
        && (c & 0x1C0) / 64 <= modifiers.insertions_)
      errorCode_[(c & 0x1C0) / 64] += (uint64_t) 1 << c % 64;
  }
}
