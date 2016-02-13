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

#include "tnfa_model_edits.h"
#include "tnfa_start_state_edits.h"
#include "tnfa_final_state_edits.h"

TNFAModelEdits::TNFAModelEdits(const Modifiers &modifiers,
                               const std::string& pattern) :
  TNFAModel(pattern),
  startState_(nullptr),
  errorCode_(0)
{
  TNFAStateEdits *currentState;
  ModifiersToErrorCode(modifiers);

  // Set up states
  startState_ = currentState = new TNFAStartStateEdits( errorCode_ );
  for (char c : pattern_) {
    currentState->setOutPtr(new TNFAStateEdits( c ));
    currentState = currentState->getOutPtr();
  }
  currentState->setOutPtr(new TNFAFinalStateEdits(pattern.length()
                                                  + modifiers.insertions_
                                                  - modifiers.deletions_,
                                                  modifiers.mismatches_ +
                                                  modifiers.deletions_ +
                                                  modifiers.insertions_
                                                  ));
}

void TNFAModelEdits::Initialize(std::string::const_iterator pos,
                                std::string::const_iterator max_pos,
                                bool stay_at_pos ) {
  stay_sequence_iterator_ = sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
  stay_at_pos_ = stay_at_pos;
  matches.clear();
  stateLists_[ 0 ].clear();
  stateLists_[ 1 ].clear();
  listNo_ = ++listID_ % 2;
  startState_->addToList(0,
                         listNo_,
                         sequence_iterator_,
                         stateLists_,
                         matchMap_,
                         listID_);
}

bool TNFAModelEdits::FindMatch() {

  if (!matches.empty()) {
    matches.pop_back();
    if (!matches.empty())
      return true;
  }

  matchMap_.clear();

  for (; sequence_iterator_ != sequence_iterator_end_ && matchMap_.empty();
       sequence_iterator_++)
  {
    while (*sequence_iterator_ == 'N')
      if( ++sequence_iterator_ == sequence_iterator_end_ )
        return false;
      

    stateLists_[listNo_ = ++listID_ % 2].clear();

    if(!stay_at_pos_) {
      startState_->addToList(0,
                             listNo_,
                             sequence_iterator_,
                             stateLists_,
                             matchMap_,
                             listID_);
    }

    for (TNFAStateEdits *s : stateLists_[!listNo_]) {
      s->addOutStates(listNo_,
                      sequence_iterator_,
                      stateLists_,
                      matchMap_,
                      listID_);
    }
  }

  for (auto matchPair : matchMap_) {
    if (stay_at_pos_)
      matches.push_back(
        Match(stay_sequence_iterator_, matchPair.first, matchPair.second)
      );
    else
      matches.push_back(
        Match(sequence_iterator_ - matchPair.first, matchPair.first, matchPair.second)
      );
  }
  
  return !matches.empty();
}

void TNFAModelEdits::ModifiersToErrorCode(const Modifiers &modifiers) {
  errorCode_ = modifiers.max_edits_;
}

const Match& TNFAModelEdits::GetMatch() const
{ return matches.back(); }
