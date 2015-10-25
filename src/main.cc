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

#include <stdio.h>

#include <ptnode.h>
#include <interpreter.h>
#include <seq_entry.h>
#include <fasta_reader.h>

#include "optparse.h"
#include "pattern_io.h"
#include "pu_factory/sanity_checker.h"
#include "pu_factory/pattern_unit_creator.h"

int main(int argc, char *argv[]) {
  //Parse cmd-line options
  OptParse opt_parse(argc, (char**)argv);

  //Extract string-patterns
  std::vector<std::string> patterns;
  if (!opt_parse.options_.pattern_file.empty()) {
    PatternIO pat_parse(opt_parse.options_.pattern_file, patterns);
  } else {
    patterns.push_back(opt_parse.options_.pattern);
  }

  //Verbose output
  if (opt_parse.options_.verbose) {
    opt_parse.PrintVersion();
    std::cerr << std::endl;
    opt_parse.PrintCommandLine();
    std::cerr << std::endl << std::endl;
    opt_parse.PrintOptions();

    std::cerr << std::endl << "Patterns:" << std::endl;

    for (auto it : patterns) {
      std::cerr << "  " << it << std::endl;
    }
  }

  //Pattern parser classes
  SeqScan::Interpreter parse_tree_generator;
  SeqScan::SanityChecker parse_tree_checker;
  SeqScan::PatternUnitCreator pattern_unit_factory;

  for (auto& file_path : opt_parse.files_){

    //Set up fasta reader
    FastaReader fasta_reader(file_path);

    for (auto& raw_pat : patterns){

      //Parse and check string-pattern
      SeqScan::PTNode* parse_tree = parse_tree_generator.parse(raw_pat);

      if (parse_tree==NULL){
        std::cerr<<"Error parsing pattern: "<<raw_pat<<std::endl;
        continue;
      }

      if (!parse_tree_checker.is_sane(parse_tree)){
        std::cerr<<"Insane pattern: "<<raw_pat<<std::endl;
        continue;
      }

      std::unique_ptr<PatternUnit> pattern = pattern_unit_factory.create_from_parse_tree(parse_tree);


      //For each SeqEntry: attempt to match pattern
      while (fasta_reader.hasNextEntry()){
        std::unique_ptr<SeqEntry> entry = fasta_reader.nextEntry();
        const std::string& seq = entry->seq();

        //Perform matching of pattern against seq
        pattern->Initialize(seq.cbegin(), seq.cend());
        while (pattern->FindMatch()) {
          const Match& match = pattern->GetMatch();
          match.Print(std::cout, seq.cbegin())<<std::endl;
        }

      } // end while (fasta_reader.hasNextEntry())


    } // end for (auto& raw_pat : patterns)

  } // end for (auto& file_path : opt_parse.files_)

  return EXIT_SUCCESS;
}
