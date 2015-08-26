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

#include <iostream>
#include <memory>

#include "modifiers.h"
#include "pu/composite_unit.h"
#include "pu/backtrack_sequence_unit.h"
#include "pu/tnfa_sequence_unit.h"

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

  Modifiers tnfa_modifiers = Modifiers::CreateMIDModifiers(1,0,0);
  unique_ptr<PatternUnit> tnfa_unit( new TNFASequenceUnit(first_modifiers, "AATCA"));

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

  //Find matches using TNFA
  num_matches = 0;
  tnfa_unit->Initialize( sequence.cbegin(), sequence.cend() );
  while(tnfa_unit->HasNextMatch()){
    Match& m = tnfa_unit->NextMatch();
    printf( "Starting position: %i\tLength: %i\n", m.pos, m.len);
    num_matches++;
  }
  cout<<"Found "<<num_matches<<" TNFA matches"<<endl;

  return 0;
}
