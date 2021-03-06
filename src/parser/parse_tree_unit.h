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


#ifndef SEQSCAN_PARSER_PARSE_TREE_UNIT_H_
#define SEQSCAN_PARSER_PARSE_TREE_UNIT_H_

#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

namespace SeqScan {

/**
 * Prefix modifiers for a ParseTreeNode.
 * Stores all modifiers that can appear before a pattern unit.
 */
class PTPreModifier{
 public:
  PTPreModifier();

  bool tilde_;
  bool hat_;
  bool less_;
  bool start_anchor_;

  std::string str() const;
};

/**
 * Suffix modifiers for a ParseTreeNode.
 * Stores all modifiers that can appear after a pattern unit.
 */
class PTSufModifier{
 public:
  PTSufModifier();

  int mismatches_;
  int insertions_;
  int deletions_;
  int indels_;
  int edits_;
  bool end_anchor_;

  std::string str() const;
};


/**
 * Container class for pattern units that have been parsed.
 * Anything properties that are necessary to define the pattern unit are stored in this class. This means:
 *   - For sequence units: A sequence (sequence_)
 *   - For reference units: A string representation of the referenced label (referenced_label_
 *
 *
 * Any optional modifiers
 * are stored in pre_modifier_ or suf_modifier_ (depending on where they belong according to the pattern syntax).
 */
class ParseTreeUnit
{
 public:
  enum UnitType {
    Composite, Sequence, Repeat, Reference, Range, Or, Group
  };

  ParseTreeUnit(const UnitType type);
  ParseTreeUnit(const std::string &sequence);
  ~ParseTreeUnit();

  std::string Str(size_t indent = 0) const;

  /**
   * Returns a compact string representation of the tree structure and overall types
   * used for debugging. For example, the pattern:
   * AA p1=~CC (N{2,4}|2..4)
   * will have the compact parsed representation
   * (SEQ,SEQ,OR(REP(SEQ),RANGE))
   */
  std::string Repr() const;

  const UnitType node_type_;

  std::vector<ParseTreeUnit*> children_;

  std::string sequence_;
  std::string label_;
  std::string referenced_label_;

  int  min_repeats_;
  int  max_repeats_;
  bool open_repeats_;
  int  range_min_;
  int  range_max_;
  void AddModifier(PTPreModifier *m);
  void AddModifier(PTSufModifier *m);

  PTPreModifier pre_modifier_;
  PTSufModifier suf_modifier_;
};
}  // namespace SeqScan

#endif  // SEQSCAN_PARSER_PARSE_TREE_UNIT_H
