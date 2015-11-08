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

#include <memory>

#include "catch.h"
#include "../src/modifiers.h"
#include "../src/pu/backtrack_unit.h"

using namespace std;

TEST_CASE("Test sequence with fuzzy matching", "[sequence,fuzzy matching]") {

  // Set up test pattern "AATCA/1,0,0"
  ResMatcher rm(kMatrix6);
  Modifiers first_modifiers = Modifiers::CreateMIDModifiers(rm, 1, 0, 0);
  unique_ptr<PatternUnit> first_unit(new BacktrackUnit(first_modifiers, "AATCA"));

  // Define sequence
  string sequence = "AUGAUGAUGAATTATTTTTTCGGG";
  int num_matches = 0;

  SECTION("test match with 1 mismatch") {
    first_unit->Initialize(sequence.cbegin(), sequence.cend());
    while (first_unit->FindMatch()) {
      const Match& m = first_unit->GetMatch();
      REQUIRE(m.pos-sequence.cbegin() == 9);
      REQUIRE(m.len == 5);
      REQUIRE(m.edits == 1);
      num_matches++;
    }

    REQUIRE(num_matches == 1);
  }
}
