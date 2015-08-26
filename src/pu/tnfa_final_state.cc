/*
 * finalState.cpp
 *
 * Implementation of FinalState as described in finalState.hpp
 *
 * Written by Sune Grud Enevoldsen
 * May 2015
 */

#include "tnfa_final_state.h"

extern bool showAllMatches;

TNFAFinalState::TNFAFinalState() : TNFAState( 0 ) {}

void TNFAFinalState::addOutStates(bool, std::string::const_iterator,
                                  vector< TNFAState * > [],
                                  vector< Match > &, uint32_t) {}

void TNFAFinalState::addEpsilonTransitions(bool, std::string::const_iterator,
                                           vector< TNFAState * >[],
                                           vector< Match > &matches, uint32_t listID)
{
  matches.push_back(Match( listID, 0, 0 ));
}
