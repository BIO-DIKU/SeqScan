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

#ifndef PU_TNFA_FINAL_STATE_512_H_
#define PU_TNFA_FINAL_STATE_512_H_

#include <iostream>
#include <vector>
#include <string>

#include "tnfa_state_512.h"


class TNFAFinalState512 : public TNFAState512 {
public:

  TNFAFinalState512(int len, int edits);

  void addEpsilonTransitions(bool,
                             std::string::const_iterator,
                             std::vector< TNFAState512 * > [2],
                             std::unordered_map<int, int> &,
                             uint32_t);

  void addOutStates(bool,
                    std::string::const_iterator,
                    std::vector< TNFAState512 * > [2],
                    std::unordered_map<int, int> &,
                    uint32_t);
private:

  int patternLength_;

  int maxEdits_;

};

#endif  // PU_TNFA_FINAL_STATE_H_
