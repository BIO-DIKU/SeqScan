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

#ifndef COMPOSITE_UNIT_H_
#define COMPOSITE_UNIT_H_

#include <vector>
#include <set>
#include <string>
#include "pattern_unit.h"

/**
 * A pattern unit composed of other units (child units) that must match subsequences in order and
 * without gaps. Child units are delivered to the CompositeUnit using the AddUnit.
 */
class CompositeUnit: public PatternUnit {
public:
  /// Construct a CompositeUnit with the specified modifiers
  CompositeUnit(const Modifiers &modifiers);

  /** Add the specified child unit. Ownership of the passed argument is taken over. */
  void AddUnit(std::unique_ptr<PatternUnit> &unit);

  void Initialize(std::string::const_iterator pos,
                  std::string::const_iterator max_pos,
                  bool stay_at_pos = false);
  bool FindMatch() override;

  const Match& GetMatch() override;

  std::ostream&Print(std::ostream &os) const override;

private:
  /** The child units. */
  std::vector< std::unique_ptr<PatternUnit> > child_units_;

  /** When FindMatch returns true each entry in child_units_ will have a valid match, which this
   * function composes into composite_match_. */
  void ComposeMatches();

  /** The match that gets returned when calling GetMatch. This member gets reallocated each time
   * FindMatch returns true. */
  Match* composite_match_;

  /** The end of the sequence iterator. */
  std::string::const_iterator sequence_iterator_end_;

  /** Indicates whether FindMatch should search for matches starting at other positions than the
   * one indicated in Initialize */
  bool stay_at_pos_;

  /** The current child-unit, i.e. the first unit that hasn't detected a match. If
   * current_unit_==child_units_.size() then all child-units have found consecutive matches. */
  size_t current_unit_;

};

std::ostream& operator<<(std::ostream& os, const CompositeUnit& obj);

#endif  // COMPOSITE_UNIT_H_
