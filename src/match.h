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

#ifndef SEQSCAN_MATCH_H_
#define SEQSCAN_MATCH_H_

#include <string>
#include <iostream>
#include <vector>

/**
 * A match is a substring of a sequence which matches a pattern unit. In addition to the
 * substring a match also stores the number of string edits the pattern unit used. Some pattern
 * units are composed of sub-units so the matches they return will have corresponding sub-matches
 * as well.
 */
class Match {
public:
  /** Construct a match with no sub-matches.  */
  Match(const std::string::const_iterator &pos, const int &len, const int &edits);

  /** Construct a match with sub-matches.  */
  Match(const std::vector< Match >& sub_matches);

  /** An iterator position of the first matched character. */
  const std::string::const_iterator pos;

  /** The number of characters in the match. */
  const int len;

  /** The number of edits used to generate this match. */
  const int edits;

  /** Less-than operator used for storing matches in ordered sets. A match a is less than b if
   * a.pos precedes b.pos. If a.pos==b.pos then a<b if and only if a.len<b.len. */
  bool operator<(const Match& rhs) const{
    return pos==rhs.pos?len<rhs.len:pos<rhs.pos;
  }

  /**
   * Print the match to the specified stream and return the stream. If there are no sub-matches
   * the format of printing the match is:
   * seq-pos,match-len,match-edits,sub-string
   * Here, seq-pos is 1-index. For example the pattern unit 'AAAA/1,0,0' could have a match that would print:
   * 2001,4,1,ACAA
   * In order to find the absolute sequence-position the seq_start argument is provided. If the
   * match has N sub-matches the format of printing the match is:
   * sub-match1;sub-match2;...;sub-matchN
   * Where sub-matchI is the Print-formatted representation of the I'th sub-match.
   */
  std::ostream& Print(std::ostream& os, const std::string::const_iterator& seq_start) const;

private:

  /** The summed length of all matches in the supplied vector. */
  static int TotalLen(const std::vector< Match >&);

  /** The summed number of edits in all matches in the supplied vector. */
  static int TotalEdits(const std::vector< Match >&);

  /** Sub-matches of this match. Can be empty. */
  const std::vector< Match > sub_matches_;

};

#endif  // SEQSCAN_MATCH_H_
