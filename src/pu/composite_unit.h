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
#include "pattern_unit.h"

class CompositeUnit: public PatternUnit
{
public:
  CompositeUnit(const Modifiers &modifiers);

  void AddUnit(std::unique_ptr<PatternUnit> &unit);

  void Print();

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos
  );
  bool HasNextMatch();
  const Match& NextMatch();

private:
  std::vector< std::unique_ptr<PatternUnit> > punits_;

  std::set<const Match> matches_;
  std::string::const_iterator sequence_iterator_;
};

#endif  // COMPOSITE_UNIT_H_
