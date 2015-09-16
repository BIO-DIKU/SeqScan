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
#include "pu/backtrack_unit.h"
#include "pu/tnfa_unit.h"
#include "pu/repeat_unit.h"
#include "io.h"
#include "pu/reference_unit.h"
#include "pu/range_unit.h"

using namespace std;

int main(int argc, char** argv) {
  /*
  // Example of setting up the seqscan pattern "AATCA/1,0,0 TTTTTTC"
  //Modifiers top_modifiers = Modifiers::CreateStdModifiers();
  //unique_ptr<CompositeUnit> root_unit(new CompositeUnit(top_modifiers) );

  Modifiers first_modifiers = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr<PatternUnit> first_unit(new BacktrackUnit(first_modifiers, "AATCA"));

  //Modifiers second_modifiers = Modifiers::CreateStdModifiers();
  //unique_ptr<PatternUnit> second_unit(new BacktrackSequenceUnit(second_modifiers, "TTTTTTC"));

  //root_unit->AddUnit(first_unit);
  //root_unit->AddUnit(second_unit);

  //root_unit->Print();

  // Define sequence
  string sequence = "AUGAUGAUGAATTATTTTTTCGGG";

  // Find all matches in sequence
  int num_matches = 0;

  first_unit->Initialize(sequence.cbegin(), sequence.cend());
  while (first_unit->FindMatch()) {
    const Match& m = first_unit->GetMatch();
    printf("Starting position: %li\tLength: %i\tEdits: %i\n", m.pos-sequence.cbegin(), m.len, m.edits);
    num_matches++;
  }
  cout << "Found " << num_matches << " matches" << endl;

  // Find matches using TNFA
  unique_ptr<PatternUnit> tnfa_unit(new TNFAUnit(first_modifiers, "AATCA"));

  num_matches = 0;
  tnfa_unit->Initialize(sequence.cbegin(), sequence.cend());
  while (tnfa_unit->FindMatch()) {
    const Match& m = tnfa_unit->GetMatch();
    printf("Starting position: %li\tLength: %i\tEdits: %i\n", m.pos-sequence.cbegin(), m.len, m.edits);
    num_matches++;
  }
  cout << "Found " << num_matches << " TNFA matches" << endl;

  */

  /*
  // Set up test pattern "AAAAAAA/1,1,0 CCCCCCC"
  Modifiers m0 = Modifiers::CreateMIDModifiers(1, 1, 0);
//  unique_ptr <PatternUnit> pu0(new BacktrackUnit(m0, "AAAAAAA"));
  unique_ptr <PatternUnit> pu0(new TNFAUnit(m0, "AAAAAAA"));
  Modifiers m1 = Modifiers::CreateStdModifiers();
  unique_ptr <PatternUnit> pu1(new BacktrackUnit(m1, "CCCCCCC"));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> pu( new CompositeUnit(m) );
  pu->AddUnit(pu0);
  pu->AddUnit(pu1);
  */

  /*
  string sequence = "TTTAAATCCCTTT";
  cout<<"Finding all matches of '"<<(*pu)<<"' in '"<<sequence<<"'"<<endl;

  pu->Initialize(sequence.cbegin(), sequence.cend());
  while (pu->FindMatch()) {
    const Match& m = pu->GetMatch();
    printf("Starting position: %li\tLength: %i\tEdits: %i\n", m.pos-sequence.cbegin(), m.len, m.edits);
  }
  */

  /*
  // Set up test pattern "AA{2,4}"
  Modifiers m0 = Modifiers::CreateMIDModifiers(1, 0, 0);
  unique_ptr <PatternUnit> pu0(new BacktrackUnit(m0, "AA"));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<RepeatUnit> pu( new RepeatUnit(pu0, m, 2,4) );
   */

  /*
  string sequence = "TTTAAAAATCCCTTT";
  cout<<"Finding all matches of '"<<(*pu)<<"' in '"<<sequence<<"'"<<endl;

  pu->Initialize(sequence.cbegin(), sequence.cend());
  while (pu->FindMatch()) {
    const Match& m = pu->GetMatch();
    printf("Starting position: %li\tLength: %i\tEdits: %i\n", m.pos-sequence.cbegin(), m.len, m.edits);
  }
   */

  /*
  // Set up test pattern "p1=AAAAAAAA/0,2,0 p1/2,0,0"
  Modifiers m0(0,0,2,0,0,false,false,false,"p1");
  unique_ptr <PatternUnit> pu0(new BacktrackUnit(m0, "AAAAAAAA"));
  Modifiers m1 = Modifiers::CreateMIDModifiers(2,0,0);
  unique_ptr <PatternUnit> pu1(new ReferenceUnit(pu0.get(), m1));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> pu( new CompositeUnit(m) );
  pu->AddUnit(pu0);
  pu->AddUnit(pu1);
  */
  // Set up test pattern "p1=4..6 2..4 p1/2,0,0"
  Modifiers m0(0,0,0,0,0,false,false,false,"p1");
  unique_ptr <PatternUnit> pu0(new RangeUnit(m0, 12, 15));
  Modifiers m1 = Modifiers::CreateStdModifiers();
  unique_ptr <PatternUnit> pu1(new RangeUnit(m1, 2, 4));
  Modifiers m2 = Modifiers::CreateMIDModifiers(2,0,0);
  unique_ptr <PatternUnit> pu2(new ReferenceUnit(pu0.get(), m2));

  Modifiers m = Modifiers::CreateStdModifiers();
  unique_ptr<CompositeUnit> pu( new CompositeUnit(m) );
  pu->AddUnit(pu0);
  pu->AddUnit(pu1);
  pu->AddUnit(pu2);

  if(argc>1){
    const string fname = argv[argc-1];

    for (auto &head_seq_pair: IO::read_fasta(fname)){
      cout<<"Searching for '"<<(*pu)<<"' in '"<<head_seq_pair.first<<"'"<<endl;

      const string& sequence = head_seq_pair.second;

      pu->Initialize(sequence.cbegin(), sequence.cend());
      while (pu->FindMatch()) {
        const Match& m = pu->GetMatch();
        //printf("Starting position: %li\tLength: %i\tEdits: %i\n", m.pos-sequence.cbegin(), m
        //   .len, m.edits);
        m.Print(std::cout, sequence.cbegin())<<std::endl;
      }


    }

  }



  return EXIT_SUCCESS;
}

