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
 
#ifndef PU_PATTERNUNIT_H_
#define PU_PATTERNUNIT_H_

#include <string>

#include "../match.h"
#include "../modifiers.h"

/*
 * An abstract pattern unit that holds modifiers and specifies an iterator pattern over matches.
 * The return value of HasNextMatch and NextMatch are undefined before Initialize has been called. NextMatch
 * is only guaranteed to be specified if HasNextMatch returns true. The intended use is roughly as follows:
 *    unique_ptr<PatternUnit> pu = ...
 *    string sequence = ...
 *    pu->Initialize( sequence.cbegin(), sequence.cend() );
 *    while( pu->HasNextMatch() ){
 *      Match& m = pu->NextMatch();
 *      // Do something with m
 *    }
 */
class PatternUnit
{
public:
  /*
   * Construct a pattern unit with the specified modifiers
   */
  PatternUnit(const Modifiers& modifiers);

  /*
   * Initialize the pattern unit so the match iteration will start at pos
   */
  virtual void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos
  ) = 0;

  /*
   * Returns true iff there its possible to locate a match following the previous found. If NextMatch has not been
   * called it will be the match starting at the earliest position with the lowest possible length.
   * The return value of this function is only specified if Initialize has previously been called.
   */
  virtual bool HasNextMatch() = 0;

  /*
   * Returns the next match.
   * The return value of this function is only specified if HasNextMatch has previously been called and returned true.
   * The referenced match will only change on the next call to HasNextMatch.
   */
  virtual Match& NextMatch() = 0;

protected:
  const Modifiers modifiers_;

};

#endif  // PU_PATTERNUNIT_H_
