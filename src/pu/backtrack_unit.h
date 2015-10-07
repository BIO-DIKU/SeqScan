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

#ifndef SEQSCAN_PU_BACKTRACK_UNIT_H
#define SEQSCAN_PU_BACKTRACK_UNIT_H

#include <set>
#include <vector>
#include <string>
#include <iostream>

#include "pattern_unit.h"
#include "../match.h"

/**
 * A pattern unit that matches a specified string pattern using a backtracking algorithm. The
 * modifiers: mismatches, insertions, deletions, reverse, and complement are considered in matches.
 * The algorithm is conceptually similar to the one found in scan_for_matches, but bugs have been
 * corrected.
 */
class BacktrackUnit: public PatternUnit{
 public:
  /** Construct a BacktrackUnit with the specified modifiers and pattern-string. */
  BacktrackUnit(const Modifiers &modifiers, const std::string& pattern);

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false) override;

  bool FindMatch() override;

  const Match& GetMatch() const override;

  std::ostream& Print(std::ostream &os) const override;

 private:
  /** The pattern-string to search for. */
  const std::string           pattern_;

  /** The start sequence iterator. */
  std::string::const_iterator sequence_iterator_;

  /** The end sequence iterator. */
  std::string::const_iterator sequence_iterator_end_;

  /** Indicates whether FindMatch should search for matches starting at other positions than the
   * one indicated in Initialize */
  bool stay_at_pos_;

  /** The backtracking collects a set of matches for each starting-position in the sequence. Its
   * essential that this is a set (no duplicates) as backtracking can reach the same match via
   * different paths, but only one should be reported by FindMatch. Furthermore, its convenient
   * that the ordering of matches is well-defined (first, sorted by start-position, second by
   * end-position). */
  std::set<Match> last_found_matches_;

  /** The index of the match in last_found_matches_ that GetMatch should return. */
  int last_found_index_;

  /** A recursive function that fills up last_found_matches_. This is the core of the
   * backtracking algorithm. */
  void CollectMatches(std::string::const_iterator seq_it,
                      std::string::const_iterator pat_it,
                      const int M_left, const int I_left, const int D_left,
                      const int M_used, const int I_used, const int D_used);

protected:
  std::unique_ptr<PatternUnit> Clone() const override;
};

std::ostream& operator<<(std::ostream& os, const BacktrackUnit& obj);

#endif  // SEQSCAN_PU_BACKTRACK_UNIT_H
