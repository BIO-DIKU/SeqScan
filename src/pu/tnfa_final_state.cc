
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

#include "tnfa_final_state.h"

extern bool showAllMatches;

TNFAFinalState::TNFAFinalState(int len) : TNFAState( 0 ), patternLength_(len) {}

void TNFAFinalState::addOutStates(bool, std::string::const_iterator,
                                  vector< TNFAState * > [],
                                  vector< Match > &, uint32_t) {}

void TNFAFinalState::addEpsilonTransitions(bool, std::string::const_iterator,
                                           vector< TNFAState * >[],
                                           vector< Match > &matches, uint32_t listID)
{
  matches.push_back(Match(listID - patternLength_, patternLength_, 0));
}
