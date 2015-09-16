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

#include "modifiers.h"

Modifiers::Modifiers(
    const int max_edits,
    const int mismatches,
    const int insertions,
    const int deletions,
    const bool reverse,
    const bool complement,
    const bool greedy,
    const std::string label
):
    max_edits_(max_edits),
    mismatches_(mismatches),
    insertions_(insertions),
    deletions_(deletions),
    reverse_(reverse),
    complement_(complement),
    greedy_(greedy),
    label_(label)
{}

Modifiers Modifiers::CreateStdModifiers() {
  Modifiers ret(0, 0, 0, 0, false, false, false, "");
  return std::move(ret);
}

Modifiers Modifiers::CreateMIDModifiers(
    const int mismatches,
    const int insertions,
    const int deletions) {
  Modifiers ret(0, mismatches, insertions, deletions, false, false, false, "");
  return std::move(ret);
}
