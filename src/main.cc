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
#include <vector>
#include <parser/parse_tree_unit.h>
#include <parser/interpreter.h>
#include <BioIO/seq_entry.h>
#include <BioIO/fasta_reader.h>

#include "opt_parse.h"
#include "pu_factory/sanity_checker.h"
#include "pu_factory/pattern_unit_factory.h"
#include "pu_factory/pure_tnfa_factory.h"

int main(int argc, char *argv[]) {
  try {
    // Parse cmd-line options
    OptParse opt_parse(argc, (char **) argv);

    // Pattern parser classes
    SeqScan::Interpreter parse_tree_generator;
    SeqScan::SanityChecker parse_tree_checker;

    // Choose pattern unit factory based on magic keyword
    std::unique_ptr<SeqScan::PatternUnitFactory> pattern_unit_factory;
    if (opt_parse.options_.magic == "PureTNFAFactory") {
      pattern_unit_factory = std::unique_ptr<SeqScan::PatternUnitFactory>(
          new SeqScan::PureTNFAFactory(
              *opt_parse.res_matcher_.get(),
              *opt_parse.res_matcher_comp_.get())
      );
    }
    else {
      pattern_unit_factory = std::unique_ptr<SeqScan::PatternUnitFactory>(
          new SeqScan::PatternUnitFactory(
              *opt_parse.res_matcher_.get(),
              *opt_parse.res_matcher_comp_.get())
      );
    }


    // Parse, sanity-check and collect pattern units from optparser
    std::vector<std::unique_ptr<PatternUnit>> patterns;
    for (auto &raw_pat : opt_parse.patterns_) {
      // Parse string-pattern
      std::unique_ptr<SeqScan::ParseTreeUnit> parse_tree(parse_tree_generator.Parse(raw_pat));

      if (parse_tree == NULL) {
        std::cerr << "Error parsing pattern: " << raw_pat << std::endl;
        continue;
      }

      // Sanity check parse-tree
      if (!parse_tree_checker.IsSane(parse_tree.get())) {
        std::cerr << "Insane pattern: " << raw_pat << std::endl;
        std::cerr << parse_tree->Str(0) << std::endl;
        continue;
      }

      // Convert parse-tree to pattern-unit
      std::unique_ptr<PatternUnit> pattern = pattern_unit_factory->CreateFromParseTree(parse_tree.get());
      patterns.push_back(std::move(pattern));
    }

    //Start matching sequences
    for (auto &file_path : opt_parse.files_) {
      // Set up fasta reader
      FastaReader fasta_reader(file_path);

      // For each SeqEntry: attempt to match pattern
      while (fasta_reader.HasNextEntry()) {
        std::unique_ptr<SeqEntry> entry = fasta_reader.NextEntry();
        const std::string &seq = entry->seq();

        for (auto &pattern : patterns) {
          // Perform matching of pattern against seq
          pattern->Initialize(seq.cbegin(), seq.cend());
          while (pattern->FindMatch()) {
            const Match &match = pattern->GetMatch();

            std::cout << entry->name() << "\t+\t";
            match.Print(std::cout, seq.cbegin());
            std::cout << "\t" << match.len << std::endl;
          }
        }
      }
    }
  }catch(const std::exception& e){
    std::cout<<"ERROR, "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
