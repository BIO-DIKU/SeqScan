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
#include <pu/backtrackers/backtrack_mid_unit.h>
#include <pu/group_unit.h>

#include "../catch.h"

#include "../../src/modifiers.h"
#include "../../src/match.h"
#include "../../src/pu/repeat_unit.h"

using namespace std;

/*
 * AAC{2};
 * TTAACAATTT       0 match
 * TTAACAACTT       1 match
 * TTAACAAC         1 match
 * AACAACTT         1 match
 *
 *
 * AAC{2,3}
 * TTAACTT          No match
 * TTAACAACTT       1 match
 * TTAACAACAACTT    1 match
 * TTAACAACAACAACTT 2 matches
 *
 * AAC/0,1,1{3}
 * TTAACAATCACTT    1 match (0 edits, 1 ins, 1 del)
 * TTAACACAATCTT    1 match (0 edits, 1 del, 1 ins)
 *
 * [AC]{4}
 * TTCCACTT         Match
 * TTCCATT          No match
 */


TEST_CASE("Fixed number of repeats", "[repeat]") {
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu_i(new BacktrackMIDUnit(modifiers, "AAC"));
  unique_ptr<PatternUnit> pu(new RepeatUnit(pu_i, modifiers, 2,2));

  SECTION("First repeat match but second doesnt") {
    string sequence = "TTAACAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("Two repeat match") {
    string sequence = "TTAACAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 6);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  // TTAACAAC         1 match
  SECTION("A repeat match at the end of the sequence") {
    string sequence = "TTAACAAC";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 6);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  // AACAACTT         1 match
  SECTION("A repeat match at the beginning of the sequence") {
    string sequence = "AACAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match& m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 0);
    REQUIRE(m1.len == 6);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }
}


TEST_CASE("Interval of repeats", "[repeat]") {
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu_i(new BacktrackMIDUnit(modifiers, "AAC"));
  unique_ptr<PatternUnit> pu(new RepeatUnit(pu_i, modifiers, 2, 3));

  //TTAACTT          No match
  SECTION("One seq-repeat for 2-3 rep pat: No match") {
    string sequence = "TTAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
  }

  //TTAACAACTT       1 match
  SECTION("Two seq-repeat for 2-3 rep pat matches") {
    string sequence = "TTAACAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 6);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  //TTAACAACAACTT    2 matches
  SECTION("Three seq-repeat for 2-3 rep pat matches twice") {
    string sequence = "TTAACAACAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 9);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());
    const Match &m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 5);
    REQUIRE(m2.len == 6);
    REQUIRE(m2.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

  //TTAACAACAACAACTT 3 matches
  SECTION("Four seq-repeat for 2-3 rep pat matches thrice") {
    string sequence = "TTAACAACAACAACTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());

    REQUIRE(pu->FindMatch());
    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 9);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());
    const Match &m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 5);
    REQUIRE(m2.len == 9);
    REQUIRE(m2.edits == 0);

    REQUIRE(pu->FindMatch());
    const Match &m3 = pu->GetMatch();
    REQUIRE(m3.pos - sequence.cbegin() == 8);
    REQUIRE(m3.len == 6);
    REQUIRE(m3.edits == 0);

    REQUIRE(!pu->FindMatch());
  }
}

TEST_CASE("Repeat of group unit", "[repeat]") {
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu_i(new GroupUnit(modifiers, "A", false));
  unique_ptr<PatternUnit> pu_23(new RepeatUnit(pu_i, modifiers, 2, 3));
  unique_ptr<PatternUnit> pu_2u(new RepeatUnit(pu_i, modifiers, 2, -1));

  SECTION("Repeated group match in the middle of the sequence") {
    string sequence = "TTAACTT";
    pu_23->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu_23->FindMatch());
    const Match &m1 = pu_23->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 2);
    REQUIRE(m1.edits == 0);
  }

  SECTION("Repeated group match at the end of the sequence") {
    string sequence = "TTAAA";
    pu_23->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu_23->FindMatch());
    const Match &m1 = pu_23->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 3);
    REQUIRE(m1.edits == 0);
  }

  SECTION("Unlimited repeat group match at the end of the sequence") {
    string sequence = "TTAAA";
    pu_2u->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu_2u->FindMatch());
    const Match &m1 = pu_2u->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 3);
    REQUIRE(m1.edits == 0);
  }

  SECTION("Unlimited repeat group match in middle of the sequence") {
    string sequence = "TTAAAAACCC";
    pu_2u->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu_2u->FindMatch());
    const Match &m1 = pu_2u->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 2);
    REQUIRE(m1.len == 5);
    REQUIRE(m1.edits == 0);
  }
}
