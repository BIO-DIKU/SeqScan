#include "catch.h"

#include <memory>
#include <iostream>

#include "../modifiers.h"
#include "../match.h"
#include "../pu/backtrack_unit.h"
#include "../pu/composite_unit.h"


using namespace std;

TEST_CASE( "Composite unit with two children. No fuzziness.", "[composite]" ) {

  // Set up test pattern "AAA/0,0,0 CCC/0,0,0"
  Modifiers m0 = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu0(new BacktrackUnit(m0, "AAA"));
  Modifiers m1 = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr<PatternUnit> pu1(new BacktrackUnit(m1, "CCC"));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> pu(new CompositeUnit(m));
  pu->AddUnit(pu0);
  pu->AddUnit(pu1);


  SECTION("No match") {
    string sequence = "TTTAATCCCTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(!pu->FindMatch());
  }

  SECTION("One direct match") {
    string sequence = "TTTAAACCCTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE(pu->FindMatch());
    REQUIRE(pu->GetMatch().pos - sequence.cbegin() == 3);
    REQUIRE(pu->GetMatch().len == 6);
    REQUIRE(pu->GetMatch().edits == 0);
  }

}

TEST_CASE( "Composite unit with two children. With fuzziness.", "[composite]")
{
  // Set up test pattern "AAA/0,1,0 CCC/0,0,0"
  Modifiers m0 = Modifiers::CreateMIDModifiers(0, 1, 0);
  unique_ptr <PatternUnit> pu0(new BacktrackUnit(m0, "AAA"));
  Modifiers m1 = Modifiers::CreateMIDModifiers(0, 0, 0);
  unique_ptr <PatternUnit> pu1(new BacktrackUnit(m1, "CCC"));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> pu( new CompositeUnit(m) );
  pu->AddUnit(pu0);
  pu->AddUnit(pu1);

  SECTION("One match requiring backtracking between units"){
    string sequence = "TTTAAATCCCTTT";
    pu->Initialize(sequence.cbegin(), sequence.cend());
    REQUIRE( pu->FindMatch() );
    REQUIRE( pu->GetMatch().pos-sequence.cbegin() == 3 );
    REQUIRE( pu->GetMatch().len == 7 );
    REQUIRE( pu->GetMatch().edits == 1 );
  }
}

