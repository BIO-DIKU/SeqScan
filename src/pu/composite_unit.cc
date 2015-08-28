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

#include <iostream>

#include "composite_unit.h"   // TODO(Rasmus): include directory when naming .h files

CompositeUnit::CompositeUnit(const Modifiers &modifiers) :
    PatternUnit(modifiers)
{}

void CompositeUnit::AddUnit(std::unique_ptr<PatternUnit> &unit) {
  punits_.push_back(std::move(unit));
}

void CompositeUnit::Print() {
  std::cout << "CompositeUnit contains " << punits_.size() <<
    " units" << std::endl;
}

void CompositeUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos
) {
  punits_.at(0)->Initialize(pos, max_pos);
  sequence_iterator_ = pos;
  sequence_iterator_end_ = max_pos;
}

bool CompositeUnit::HasNextMatch() {
  return false;
}

const Match& CompositeUnit::NextMatch() {
  if(matches_.empty())
    matches_.insert( Match(sequence_iterator_,0,0) );

  return *matches_.begin();
}
