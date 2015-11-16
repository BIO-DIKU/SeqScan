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
class SanityChecker {
 public:

  /**
   * Performs sanity checks on the specified parse tree. Prints errors to
   * cerr and returns false if anything appears that will make the search
   * with PatternUnit break down.
   */
  bool is_sane(const ParseTreeUnit *parse_tree);

 private:
  bool is_sane(const ParseTreeUnit *parse_tree, std::set<std::string>& visited_labels);

  bool check_reference(const ParseTreeUnit *node, std::set<std::string>& visited_labels);
  bool check_sequence(const ParseTreeUnit *node);
  bool check_composite(const ParseTreeUnit *node, std::set<std::string>& visited_labels);
  bool check_repeat(const ParseTreeUnit *node, std::set<std::string>& visited_labels);

};
} // namespace SeqScan

#endif  // SEQSCAN_PU_FACTORY_SANITY_CHECKER_H_
