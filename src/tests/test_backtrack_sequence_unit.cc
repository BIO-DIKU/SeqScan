
#include "catch.h"

#include <memory>
#include <iostream>

#include "../modifiers.h"
#include "../match.h"
#include "../pu/backtrack_sequence_unit.h"


using namespace std;

TEST_CASE( "Test backtrack sequence unit matching without fuzziness", "[backtrack,exact]" ) {

  // Set up test pattern "AAAA/0,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu(new BacktrackSequenceUnit(modifiers, "AAAA"));

  SECTION( "0 matches" ){
    string sequence = "TTTAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );

    sequence = "AAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );

    sequence = "TTTAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );
  }

  SECTION( "1 match" ){
    string sequence = "TTTAAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );

    const Match& m1 = pu->NextMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE( !pu->HasNextMatch() );

    sequence = "AAAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );

    const Match& m2 = pu->NextMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 0 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE( !pu->HasNextMatch() );

    sequence = "TTTAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );
  }

  SECTION( "2 non-overlapping matches" ){
    string sequence = "TAAAATAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->HasNextMatch());

    const Match& m1 = pu->NextMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 1 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE(pu->HasNextMatch());

    const Match& m2 = pu->NextMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 6 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE(!pu->HasNextMatch());
  }

  SECTION( "2 overlapping matches" ){
    string sequence = "TTTAAAAAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->HasNextMatch());

    const Match& m1 = pu->NextMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 0 );

    REQUIRE(pu->HasNextMatch());

    const Match& m2 = pu->NextMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 4 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 0 );

    REQUIRE(!pu->HasNextMatch());

    sequence = "AAAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->HasNextMatch());
    REQUIRE(pu->HasNextMatch());
    REQUIRE(!pu->HasNextMatch());
  }
}


TEST_CASE( "Test backtrack sequence unit matching with mismatches", "[backtrack,mismatches]" ) {

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr<PatternUnit> pu(new BacktrackSequenceUnit(modifiers, "AAAA"));

  // Set up test pattern "AAAA/1,0,0"
  Modifiers modifiers_2 = Modifiers::CreateMIDModifiers(2, 0, 0);
  unique_ptr<PatternUnit> pu_2(new BacktrackSequenceUnit(modifiers, "AAAA"));

  SECTION( "0 matches" ){
    string sequence = "TTTAATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );

    sequence = "AATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );

    sequence = "TTTAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( !pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );
  }

  SECTION( "1 match" ){
    string sequence = "TTTAACATTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );

    const Match& m1 = pu->NextMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 3 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 1 );

    REQUIRE( !pu->HasNextMatch() );

    sequence = "AAAGTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );

    const Match& m2 = pu->NextMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 0 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 1 );

    REQUIRE( !pu->HasNextMatch() );

    sequence = "CCCUAAA";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->HasNextMatch() );
    REQUIRE( !pu->HasNextMatch() );
  }

  SECTION( "overlapping matches" ){
    string sequence = "TTTAAACAT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->HasNextMatch());

    const Match& m1 = pu->NextMatch();
    REQUIRE( m1.pos-sequence.cbegin() == 2 );
    REQUIRE( m1.len == 4 );
    REQUIRE( m1.edits == 1 );

    REQUIRE(pu->HasNextMatch());

    const Match& m2 = pu->NextMatch();
    REQUIRE( m2.pos-sequence.cbegin() == 3 );
    REQUIRE( m2.len == 4 );
    REQUIRE( m2.edits == 1 );

    REQUIRE(pu->HasNextMatch());

    const Match& m3 = pu->NextMatch();
    REQUIRE( m3.pos-sequence.cbegin() == 4 );
    REQUIRE( m3.len == 4 );
    REQUIRE( m3.edits == 1 );

    REQUIRE(!pu->HasNextMatch());
  }
}
