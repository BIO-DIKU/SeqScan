
#include "catch.h"

#include <memory>

#include "../modifiers.h"
#include "../pu/backtrack_sequence_unit.h"


using namespace std;

TEST_CASE( "Test sequence with fuzzy matching", "[sequence,fuzzy matching]" ) {

  // Set up test pattern "AATCA/1,0,0"
  Modifiers first_modifiers = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr<PatternUnit> first_unit(new BacktrackSequenceUnit(first_modifiers, "AATCA"));

  // Define sequence
  string sequence = "AUGAUGAUGAATTATTTTTTCGGG";
  int num_matches = 0;

  SECTION( "test match with 1 mismatch" ) {
    first_unit->Initialize(sequence.cbegin(), sequence.cend());
    while (first_unit->FindMatch()) {
      const Match& m = first_unit->GetMatch();
      REQUIRE( m.pos-sequence.cbegin() == 9 );
      REQUIRE( m.len == 5 );
      REQUIRE( m.edits == 1 );
      num_matches++;
    }	
    
    REQUIRE( num_matches == 1 );
  }
}
