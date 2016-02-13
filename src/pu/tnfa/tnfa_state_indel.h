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

#ifndef SEQSCAN_PU_TNFA_STATE_INDEL_H_
#define SEQSCAN_PU_TNFA_STATE_INDEL_H_

#include <inttypes.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "../../match.h"

class TNFAStateIndel {
 public:
  /*
   * Create a state on given character
   */
  TNFAStateIndel(char);

  void setOutPtr(TNFAStateIndel *);  // Set pointer to outgoing state
  TNFAStateIndel *getOutPtr();       // Get pointer to outgoing state

  /*
   * Add this state to the new state list
   */
  void addToList(uint64_t,
                 bool,
                 std::string::const_iterator,
                 std::vector< TNFAStateIndel * > [2],
                 std::unordered_map<int, int> &,
                 uint32_t);

  /*
   * Add states on outgoing transitions to new state list.
   * Only transitions "eating" a character from the input string are considered.
   */
  virtual void addOutStates(bool, std::string::const_iterator,
                            std::vector< TNFAStateIndel * > [2],
                            std::unordered_map<int, int> &,
                            uint32_t);

  /*
   * Add states on epsilon-transitions to new state list.
   * This is the complementary function to addOutStates().
   */
  virtual void addEpsilonTransitions(bool, std::string::const_iterator,
                                     std::vector< TNFAStateIndel * > [],
                                     std::unordered_map<int, int> &,
                                     uint32_t);

  // Show some info for current State. Mainly used for debugging.
  virtual void display(bool);

  static const int kErrorCodeBits = 64;
  // TODO(Sune): The following functions should probably also be static
  bool mismatches(uint64_t);  // Are mismatches allowed
  bool indels(uint64_t);  // Are insertions or deletions allowed
  uint64_t decrementMismatches(uint64_t);  // Decr. mismatches in error code
  uint64_t decrementIndels(uint64_t);  // Decr. insertions and deletions in error code
  static inline int counterToMismatches( int cnt ) { return cnt & 7; }
  static inline int counterToIndels( int cnt )  { return (cnt & 0x38) / 8; }
  //   7  = 0b000000000111
  //0x38  = 0b000000111000
protected:
  char c;  // Character to be matched
  TNFAStateIndel *out_;  // Outgoing state

  /*
   * Error codes are 64-bit integers that represent subsets of allowed errors
   * They are used to efficiently implement the decrement operations declared
   * above. Two codes are declared, so that one can be created, while the
   * other is read. If only one error code was used race conditions could
   * arise.
   */
  uint64_t errorCode_[2];

  uint32_t listID_; // Used to check if state is already added to list
};

#endif  // SEQSCAN_PU_TNFA_STATE_INDEL_H_
