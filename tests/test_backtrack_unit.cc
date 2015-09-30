
#include "catch.h"

#include <memory>
#include <iostream>

#include "../src/modifiers.h"
#include "../src/match.h"
#include "../src/pu/backtrack_unit.h"


using namespace std;

TEST_CASE( "Test backtrack sequence unit matching without fuzziness", "[backtrack,exact]" ) {

  // Set up test pattern "AAAA/0,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu(new BacktrackUnit(modifiers, "AAAA"));

  SECTION( "0 matches" ){
    string sequence = "TTTAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );

    sequence = "AAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );

    sequence = "TTTAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );
  }

  SECTION( "1 match" ){
    string sequence = "TTTAAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m1 = pu->GetMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE( !pu->FindMatch() );

    sequence = "AAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m2 = pu->GetMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 0 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE( !pu->FindMatch() );

    sequence = "TTTAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );
  }

  SECTION( "2 non-overlapping matches" ){
    string sequence = "TAAAATAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 1 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 6 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE(!pu->FindMatch());
  }

  SECTION( "2 overlapping matches" ){
    string sequence = "TTTAAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 4 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE(!pu->FindMatch());

    sequence = "AAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());
    REQUIRE(pu->FindMatch());
    REQUIRE(!pu->FindMatch());
  }
}


TEST_CASE( "Test backtrack sequence unit matching with mismatches", "[backtrack,mismatches]" ) {

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr<PatternUnit> pu(new BacktrackUnit(modifiers, "AAAA"));

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers_2 = Modifiers::CreateMIDModifiers(2, 0, 0);
  unique_ptr<PatternUnit> pu_2(new BacktrackUnit(modifiers, "AAAA"));

  SECTION( "0 matches" ){
    string sequence = "TTTAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );

    sequence = "AATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );

    sequence = "TTTAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );
  }

  SECTION( "1 match" ){
    string sequence = "TTTAACATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m1 = pu->GetMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 1 );

    REQUIRE( !pu->FindMatch() );

    sequence = "AAAGTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );

    const Match& m2 = pu->GetMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 0 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 1 );

    REQUIRE( !pu->FindMatch() );

    sequence = "CCCUAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch() );
    REQUIRE( !pu->FindMatch() );
  }

  SECTION( "overlapping matches" ){
    string sequence = "TTTAAACAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());

    const Match& m1 = pu->GetMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 2 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 1 );

    REQUIRE(pu->FindMatch());

    const Match& m2 = pu->GetMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 3 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 1 );

    REQUIRE(pu->FindMatch());

    const Match& m3 = pu->GetMatch();
    REQUIRE( m3.pos-sequence.cbegin() == 4 );
    REQUIRE( m3.len == 4 );
    REQUIRE( m3.edits == 1 );

    REQUIRE(!pu->FindMatch());
  }
}

TEST_CASE( "Backtrack unit staying at pos", "[backtrack,stay]" ) {

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr<PatternUnit> pu(new BacktrackUnit(modifiers, "AAAA"));

  SECTION("Stay-pos inside sequence; with match") {
    string sequence = "TTTAATATTT";
    pu->Initialize(sequence.cbegin() + 3, sequence.cend(), true);
    REQUIRE(pu->FindMatch());

    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 3);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 1);

    REQUIRE(!pu->FindMatch());
  }

  SECTION("Stay-pos inside sequence; no match") {
    string sequence = "TTTAATATTT";
    pu->Initialize(sequence.cbegin() + 2, sequence.cend(), true);
    REQUIRE(!pu->FindMatch());
  }


  SECTION("Stay-pos at start of sequence; with match") {
    string sequence = "AAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend(), true);
    REQUIRE(pu->FindMatch());

    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 0);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 0);

    REQUIRE(!pu->FindMatch());
  }

}


TEST_CASE( "Backtrack unit staying at pos; several matches", "[backtrack,stay]")
{

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 1, 0);
  unique_ptr<PatternUnit> pu(new BacktrackUnit(modifiers, "AAAA"));

  SECTION("Stay-pos inside sequence; several matches") {
    string sequence = "TTTAAAATTT";
    pu->Initialize(sequence.cbegin() + 3, sequence.cend(), true);
    REQUIRE(pu->FindMatch());

    const Match &m1 = pu->GetMatch();
    REQUIRE(m1.pos - sequence.cbegin() == 3);
    REQUIRE(m1.len == 4);
    REQUIRE(m1.edits == 0);

    REQUIRE(pu->FindMatch());

    const Match &m2 = pu->GetMatch();
    REQUIRE(m2.pos - sequence.cbegin() == 3);
    REQUIRE(m2.len == 5);
    REQUIRE(m2.edits == 1);

    REQUIRE(!pu->FindMatch());
  }
}
