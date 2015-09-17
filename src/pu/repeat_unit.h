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

#ifndef SEQSCAN_REPEAT_UNIT_H
#define SEQSCAN_REPEAT_UNIT_H

#include <vector>

#include "pattern_unit.h"

/**
 * A pattern unit which matches if and only if a child-unit matches a certain number of times
 * consecutively. A range of valid number of repeats can be specified. This pattern unit will
 * return matches corresponding to the maximal number of found repeats and no fewer. For example
 * the pattern AAT{2,4} will have exactly one match of length 9 in the sequence AATAATAATAAC even
 * though it could be argued that there is also two additional matches of length 6. This avoids
 * combinatorial explosions in many cases.
 *
 */
class RepeatUnit: public PatternUnit {

public:
  RepeatUnit(
      std::unique_ptr<PatternUnit> &pu,
      const Modifiers &modifiers,
      const int &min_repeats,
      const int &max_repeats
  );

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos,
      bool stay_at_pos = false
  ) override;

  bool FindMatch() override;

  const Match& GetMatch() const override;

  std::ostream& Print(std::ostream &os) const;

private:

  std::string::const_iterator sequence_iterator_end_;

  /// The child pattern units to detect repeated matches of
  std::vector< std::unique_ptr<PatternUnit> > child_units_;

  /// Minimum number of repeats
  const size_t min_repeats_;

  /// Maximum number of repeats
  const size_t max_repeats_;

  int cur_repeat_;

  /** When FindMatch returns true each entry in child_units_ from index 0 to cur_repeat_ will
   * have a valid match, which this function composes into repeat_match_. */
  void ComposeMatches();

  /** The match that gets returned when calling GetMatch. This member gets reallocated each time
   * FindMatch returns true. */
  Match* repeat_match_;
};

std::ostream& operator<<(std::ostream& os, const RepeatUnit& obj);

#endif //SEQSCAN_REPEAT_UNIT_H
