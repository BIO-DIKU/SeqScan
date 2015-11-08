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
#include <iostream>

#include "../catch.h"

#include "../../src/modifiers.h"
#include "../../src/match.h"
#include "../../src/pu/kmp_unit.h"
#include "../../src/pu/composite_unit.h"

using namespace std;

TEST_CASE("Test kmp sequence unit matching without fuzziness", "[kmp]") {
  // Set up test pattern "AAAA/0,0,0"
  ResMatcher rm(kMatrix6);
  Modifiers modifiers = Modifiers::CreateMIDModifiers(rm, 0, 0, 0);
  unique_ptr<PatternUnit> pu(new KMPUnit(modifiers, "AAAA"));

  SECTION("0 matches") {
    string sequence = "TTTAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
    REQUIRE(!pu->FindMatch());

    sequence = "AAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
    REQUIRE(!pu->FindMatch());

    sequence = "TTTAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("1 match") {
    string sequence = "TTTAAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 3);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());

    sequence = "AAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 0);
    REQUIRE(m2.len == 4);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());

    sequence = "TTTAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("2 non-overlapping matches") {
    string sequence = "TAAAATAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 1);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 6);
    REQUIRE(m2.len == 4);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  SECTION("2 overlapping matches") {
    string sequence = "TTTAAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 3);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 4);
    REQUIRE(m2.len == 4);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());

    sequence = "AAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());
    REQUIRE(pu->FindMatch());
    REQUIRE(!pu->FindMatch());
  }
}
