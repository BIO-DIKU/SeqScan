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
#include "../../src/pu/group_unit.h"
#include "../../src/pu/composite_unit.h"

using namespace std;


TEST_CASE("Matching Group Unit", "[group]") {
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu(new GroupUnit(modifiers, "GC", false));

  SECTION("with 0 matches results in no hits") {
    string sequence = "TTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("with 1 match is OK") {
    string sequence = "TTGTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 1);
    REQUIRE(m1.edits == 0);

    const Match& m2 = pu->GetMatch();
    REQUIRE(!pu->FindMatch());
  }

  SECTION("with 2 matches is OK") {
    string sequence = "TTCTTGTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 1);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 5);
    REQUIRE(m2.len == 1);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());
  }
}

TEST_CASE("Non-matching Group Unit", "[group]") {
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu(new GroupUnit(modifiers, "GC", true));

  SECTION("with 0 matches results in no hits") {
    string sequence = "GGCC";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("with 1 match is OK") {
    string sequence = "GGTCC";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 1);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  SECTION("with 2 matches is OK") {
    string sequence = "GGTCCAGG";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 1);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 5);
    REQUIRE(m2.len == 1);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());
  }
}
