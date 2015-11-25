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

#ifndef SEQSCAN_PU_FACTORY_SANITY_CHECKER_H_
#define SEQSCAN_PU_FACTORY_SANITY_CHECKER_H_

#include <set>
#include <string>

#include <parser/parse_tree_unit.h>

namespace SeqScan {

/**
 * Checks that a ParseTreeUnit from the parser is sane.
 * A ParseTreeUnit is considered sane if the PatternUnit it produces can produce meaningful matches. This class does
 * not check that the 'raw' pattern (the string specified in the optparser) has a meaningful syntax - thats the job of
 * the Interpreter.
 *
 * Examples of non-sane elements could be:
 *   - Range units with min-range > max-range
 *   - Repeat units with min-repeats > max-repeats
 *   - Sequence units with unrecognized characters for the specified sequence type (e.g. an x in a DNA sequence).
 *   - Approximate sequence with more allowed mismatches/edits/deletions than characters.
 *   - Backreferences to labels that dont exist or forward-references
 */
class SanityChecker {
 public:

  /**
   * Performs sanity checks on the specified Parse tree. Prints errors to cerr and returns false if anything appears
   * that will make the search with PatternUnit break down.
   */
  bool IsSane(const ParseTreeUnit *parse_tree);

 private:
  /** Helper to IsSane */
  bool IsSane(const ParseTreeUnit *parse_tree, std::set<std::string> &visited_labels);

  /** Helper to IsSane which is only called if node represents a reference unit. */
  bool CheckReferences(const ParseTreeUnit *node, std::set<std::string> &visited_labels);

  /** Helper to IsSane which is only called if node represents a sequence unit. */
  bool CheckSequence(const ParseTreeUnit *node);

  /** Helper to IsSane which is only called if node represents a composite unit. */
  bool CheckComposite(const ParseTreeUnit *node, std::set<std::string> &visited_labels);

  /** Helper to IsSane which is only called if node represents a repeat unit. */
  bool CheckRepeat(const ParseTreeUnit *node, std::set<std::string> &visited_labels);

  //TODO: Add CheckGroup
  //TODO: Add CheckRange
};

} // namespace SeqScan

#endif //SEQSCAN_PU_FACTORY_SANITY_CHECKER_H_
