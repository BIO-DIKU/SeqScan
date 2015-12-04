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

#ifndef SEQSCAN_PU_BACKTRACK_EDITS_UNIT_H_
#define SEQSCAN_PU_BACKTRACK_EDITS_UNIT_H_

#include <set>
#include <vector>
#include <string>
#include <iostream>

#include "match.h"
#include "backtrack_unit.h"

/**
 * A pattern unit that matches a specified string pattern using a backtracking algorithm. The
 * modifiers: edits and complement are considered in matches.
 * The algorithm is conceptually similar to the one found in scan_for_matches, but bugs have been
 * corrected.
 */
class BacktrackEditsUnit: public BacktrackUnit{
 public:
  /** Construct a BacktrackEditsUnit with the specified modifiers and pattern-string. */
  BacktrackEditsUnit(const Modifiers &modifiers, const std::string& pattern);

  virtual bool FindMatch() override;

 protected:

  /** A recursive function that fills up last_found_matches_. This is the core of the
   * backtracking algorithm. */
  void CollectMatches(std::string::const_iterator seq_it,
                      std::string::const_iterator pat_it,
                      const int E_left,
                      const int E_used, const int I_used, const int D_used);

 protected:
  virtual std::unique_ptr<PatternUnit> Clone() const override;
};

std::ostream& operator<<(std::ostream& os, const BacktrackEditsUnit& obj);

#endif  // SEQSCAN_PU_BACKTRACK_EDITS_UNIT_H_

