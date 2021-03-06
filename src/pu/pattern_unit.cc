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

#include <sstream>
#include "pattern_unit.h"

PatternUnit::PatternUnit(const Modifiers& modifiers):
    modifiers_(modifiers)
{}

std::unique_ptr<PatternUnit> PatternUnit::Clone() const {
  std::stringstream ss;
  Print(ss);

  std::cerr << "PatternUnit::Clone() - This pattern unit (" << ss.str() << ") does not support cloning";
  throw "PatternUnit::Clone() - This pattern unit (" + ss.str() + ") does not support cloning";
}

std::ostream& operator<<(std::ostream& os, const PatternUnit& obj) {
  return obj.Print(os);
}
