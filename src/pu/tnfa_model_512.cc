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

#include "tnfa_model_512.h"

TNFAModel512::TNFAModel512(const Modifiers &modifiers,
                           const std::string& pattern) :
  pattern_(pattern),
  startState_(nullptr),
  errorCode_{ 0, 0, 0, 0, 0, 0, 0, 0 },
  listID_(0)
{
  TNFAState *currentState;
  ModifiersToErrorCode(modifiers);

  // Set up states
  startState_ = currentState = new TNFAStartState( errorCode_ );
  for (char c : pattern_) {
    currentState->setOutPtr(new TNFAState( c ));
    currentState = currentState->getOutPtr();
  }
  currentState->setOutPtr(new TNFAFinalState(pattern.length()
                                             + modifiers.insertions_
                                             - modifiers.deletions_,
                                             modifiers.mismatches_ +
                                             modifiers.deletions_ +
                                             modifiers.insertions_
                                             ));
}

void TNFAModel512::Initialize(std::string::const_iterator pos,
                                  std::string::const_iterator max_pos,
                                  bool stay_at_pos ) {
  sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;
  matches.clear();
  stateLists_[ 0 ].clear();
  stateLists_[ 1 ].clear();
  listNo_ = ++listID_ % 2;
  startState_->addToList(TNFAState::newCode,
                         listNo_,
                         sequence_iterator_,
                         stateLists_,
                         matchMap_,
                         listID_);
}

bool TNFAModel512::FindMatch() {

  if (!matches.empty()) {
    matches.pop_back();
    if (!matches.empty())
      return true;
  }

  matchMap_.clear();

  for (; sequence_iterator_ != sequence_iterator_end_ && matchMap_.empty();
       sequence_iterator_++)
  {
    stateLists_[listNo_ = ++listID_ % 2].clear();

    if(!stay_at_pos_) {
      startState_->addToList(TNFAState::newCode,
                             listNo_,
                             sequence_iterator_,
                             stateLists_,
                             matchMap_,
                             listID_);
    }

    for (TNFAState *s : stateLists_[!listNo_]) {
      s->addOutStates(listNo_,
                      sequence_iterator_,
                      stateLists_,
                      matchMap_,
                      listID_);
    }
  }

  for (auto matchPair : matchMap_)
    matches.push_back(
        Match(sequence_iterator_ - matchPair.first, matchPair.first, matchPair.second)
    );

  return !matches.empty();
}

void TNFAModel512::ModifiersToErrorCode(const Modifiers &modifiers) {
  for (int c = 0; c < TNFAState::kErrorCodeBits; c++) {
    if (TNFAState::counterToMismatches(c) <= modifiers.mismatches_ &&
        TNFAState::counterToDeletions(c)  <= modifiers.deletions_  &&
        TNFAState::counterToInsertions(c) <= modifiers.insertions_)
    {
      errorCode_[ TNFAState::counterToInsertions(c) ] += (uint64_t) 1 << c % 64;
    }
  }
}

const Match& TNFAModel512::GetMatch() const
{ return matches.back(); }
