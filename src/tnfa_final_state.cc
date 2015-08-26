/*
 * finalState.cpp
 *
 * Implementation of FinalState as described in finalState.hpp
 *
 * Written by Sune Grud Enevoldsen
 * May 2015
 */

#include "tnfa_final_state.hpp"

extern bool showAllMatches;

TNFAFinalState::TNFAFinalState() : State( 0 ) {}

void TNFAFinalState::addOutStates() {}

void TNFAFinalState::addEpsilonTransitions()
{
  if( partialMatches && ( showAllMatches || lastMatch != pathTag ) ) {
    if( stringPos - pathTag > 1000 )
      std::cout << "Submatch: " << pathTag - 1 << " ... "
		<< stringPos - 1 << std::endl;
    found = true;
    if( !showAllMatches )
      lastMatch = pathTag;
  }
}
