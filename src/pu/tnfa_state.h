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

#ifndef TNFA_STATE_HPP
#define TNFA_STATE_HPP

#include <vector>
#include <inttypes.h>
#include <string>

#include "../match.h"

using std::vector;

class TNFAState {
public:
  /*
   * Create a state on given character
   */
  TNFAState( char );

  void setOutPtr(TNFAState *); // Set pointer to outgoing state
  TNFAState *getOutPtr(); // Get pointer to outgoing state

  /*
   * Add this state to the new state list
   */
  void addToList(uint64_t [ 8 ], uint32_t, bool, std::string::const_iterator,
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
  
  bool mismatches( uint64_t [ 8 ] ); // Are mismatches allowed
  bool insertions( uint64_t [ 8 ] ); // Are insertions allowed
  bool deletions( uint64_t [ 8 ] ); // Are deletions allowed
  uint64_t *decrementMismatches( uint64_t [ 8 ] ); // Decrement mismatches in error code
  uint64_t *decrementInsertions( uint64_t [ 8 ] ); // Decrement insertions in error code
  uint64_t *decrementDeletions( uint64_t [ 8 ] ); // Decrement deletions in error code
  static uint64_t newCode[ 8 ];
protected:
  char c; // Character to be matched
  TNFAState *out_; // Outgoing state
  std::string::const_iterator *listID; // used check if state is already added to list
  uint32_t pathTag; // Tag recording beginning index of matching substring

  /*
   * Error codes are 64-bit integers that represent subsets of allowed errors
   * They are used to efficiently implement the decrement operations declared above.
   * Two codes are declared, so that one can be created, while the other is read.
   * If only one error code was used race conditions could arise.
   */
  uint64_t errorCode[ 2 ][ 8 ];
  uint32_t listID_;
};

#endif