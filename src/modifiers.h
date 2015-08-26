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

#ifndef MODIFIERS_H_
#define MODIFIERS_H_

#include <memory>

class Modifiers {
 public:
  Modifiers(
      const int max_edits,
      const int mismatches,
      const int insertions,
      const int deletions,
      const int min_repeats,
      const int max_repeats,
      const bool reverse,
      const bool complement,
      const bool greedy);

  const int max_edits_;
  const int mismatches_;
  const int insertions_;
  const int deletions_;
  const int min_repeats_;
  const int max_repeats_;
  const bool reverse_;
  const bool complement_;
  const bool greedy_;

  static Modifiers CreateMIDModifiers(const int mismatches,
      const int insertions, const int deletions);
  static Modifiers CreateStdModifiers();
};


#endif  // MODIFIERS_H_
