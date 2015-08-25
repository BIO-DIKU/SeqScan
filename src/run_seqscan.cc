
#include <iostream>
#include <memory>

#include "modifiers.h"
#include "pu/composite_unit.h"
#include "pu/backtrack_sequence_unit.h"

using namespace std;

int main()
{
  // Example of setting up the seqscan pattern "AATCA/1,0,0 TTTTTTC"
  Modifiers top_modifiers = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> root_unit( new CompositeUnit(top_modifiers) );

  Modifiers first_modifiers = Modifiers::CreateMIDModifiers(1,0,0);
  unique_ptr<PatternUnit> first_unit( new BacktrackSequenceUnit(first_modifiers, "AATCA"));

  Modifiers second_modifiers = Modifiers::CreateStdModifiers();
  unique_ptr<PatternUnit> second_unit( new BacktrackSequenceUnit(second_modifiers, "TTTTTTC"));

  root_unit->AddUnit(first_unit);
  root_unit->AddUnit(second_unit);

  root_unit->Print();

  // Define sequence
  string sequence = "AUGAUGAUGAATTATTTTTTCGGG";

  //Find all matches in sequence
  int num_matches = 0;
  root_unit->Initialize( sequence.cbegin(), sequence.cend() );
  while(root_unit->HasNextMatch()){
    Match& m = root_unit->NextMatch();
    // TODO: Do something with m
    num_matches++;
  }
  cout<<"Found "<<num_matches<<" matches"<<endl;
	return 0;
}
