/*
 * finalState.hpp
 *
 * FinalState is the final State in an NFA.
 * When searching for partial matches and a FinalState is encountered, the indexes
 * of the matching substring is written to stdout.
 *
 * Detailed function descriptions are given in state.hpp
 *
 * Written by Sune Grud Enevoldsen
 * May 2015
 */

#ifndef TNFA_FINAL_STATE_H
#define TNFA_FINAL_STATE_H

#include <iostream>
#include "tnfa_state.h"

class TNFAFinalState : public TNFAState {
 public:
  TNFAFinalState();
  void addEpsilonTransitions(bool, std::string::const_iterator,
                             vector< TNFAState * > [2], vector< Match > &, uint32_t);
  void addOutStates(bool, std::string::const_iterator,
                    vector< TNFAState * > [2], vector< Match > &, uint32_t);
 private:
};

#endif
