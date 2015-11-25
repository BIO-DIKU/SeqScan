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

#ifndef SEQSCAN_PU_BACKTRACK_INDEL_UNIT_H_
#define SEQSCAN_PU_BACKTRACK_INDEL_UNIT_H_

#include <set>
#include <vector>
#include <string>
#include <iostream>

#include "pattern_unit.h"
#include "../match.h"

/**
 * A pattern unit that matches a specified string pattern using a backtracking algorithm. The
 * modifiers: mismatches and indels are considered in matches.
 * The algorithm is conceptually similar to the one found in scan_for_matches, but bugs have been
 * corrected.
 */
class BacktrackIndelUnit: public PatternUnit{
 public:
  /** Construct a BacktrackIndelUnit with the specified modifiers and pattern-string. */
  BacktrackIndelUnit(const Modifiers &modifiers, const std::string& pattern);

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false) override;

  virtual bool FindMatch() override;

  const Match& GetMatch() const override;

  std::ostream& Print(std::ostream &os) const override;

 protected:
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
  size_t last_found_index_;

  /** A recursive function that fills up last_found_matches_. This is the core of the
   * backtracking algorithm. */
  void CollectMatches(std::string::const_iterator seq_it,
                      std::string::const_iterator pat_it,
                      const int M_left, const int ID_left,
                      const int M_used, const int I_used, const int D_used);

 protected:
  virtual std::unique_ptr<PatternUnit> Clone() const override;
};

std::ostream& operator<<(std::ostream& os, const BacktrackIndelUnit& obj);

#endif  // SEQSCAN_PU_BACKTRACK_INDEL_UNIT_H_
