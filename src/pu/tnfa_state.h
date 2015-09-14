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

#ifndef PU_TNFA_STATE_H_
#define PU_TNFA_STATE_H_

#include <inttypes.h>
#include <vector>
#include <string>

#include "../match.h"

using std::vector;

class TNFAState {
 public:
  /*
   * Create a state on given character
   */
  TNFAState(char);

  void setOutPtr(TNFAState *);  // Set pointer to outgoing state
  TNFAState *getOutPtr();       // Get pointer to outgoing state

  /*
   * Add this state to the new state list
   */
  void addToList(uint64_t[8], bool, std::string::const_iterator,
                 vector< TNFAState * > [2], vector< Match > &, uint32_t);

  /*
   * Add states on outgoing transitions to new state list.
   * Only transitions "eating" a character from the input string are considered.
   */
  virtual void addOutStates(bool, std::string::const_iterator,
                            vector< TNFAState * > [2], vector< Match > &,
                            uint32_t);

  /*
   * Add states on epsilon-transitions to new state list.
   * This is the complementary function to addOutStates().
   */
  virtual void addEpsilonTransitions(bool, std::string::const_iterator,
                                     vector< TNFAState * > [],
                                     vector< Match > &, uint32_t);

  // Show some info for current State. Mainly used for debugging.
  virtual void display(bool);

  static uint64_t newCode[8];
  static const int kErrorCodeBits = 512;
  // TODO(Sune): The following functions should probably also be static
  bool mismatches(uint64_t[8]);  // Are mismatches allowed
  bool insertions(uint64_t[8]);  // Are insertions allowed
  bool deletions(uint64_t[8]);   // Are deletions allowed
  uint64_t *decrementMismatches(uint64_t[8]);  // Decr. mismatches in error code
  uint64_t *decrementInsertions(uint64_t[8]);  // Decr. insertions in error code
  uint64_t *decrementDeletions(uint64_t[8]);   // Decr. deletions  in error code
  static inline int counterToMismatches( int cnt ) { return cnt & 7; }
  static inline int counterToDeletions( int cnt )  { return (cnt & 0x38) / 8; }
  static inline int counterToInsertions( int cnt ) { return (cnt & 0x1C0) / 64; }
 protected:
  char c;  // Character to be matched
  TNFAState *out_;  // Outgoing state

  /*
   * Error codes are 64-bit integers that represent subsets of allowed errors
   * They are used to efficiently implement the decrement operations declared
   * above. Two codes are declared, so that one can be created, while the
   * other is read. If only one error code was used race conditions could
   * arise.
   */
  uint64_t errorCode_
    [2][8];
  uint32_t listID_; // Used to check if state is already added to list
};

#endif  // PU_TNFA_STATE_H_
