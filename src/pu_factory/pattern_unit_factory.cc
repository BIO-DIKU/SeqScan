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

#include "pattern_unit_factory.h"

#include "pu/backtrack_unit.h"
#include "pu/backtrack_edits_unit.h"
#include "pu/backtrack_indel_unit.h"
#include "pu/reference_unit.h"
#include "pu/composite_unit.h"
#include "pu/repeat_unit.h"
#include "pu/range_unit.h"
#include "pu/kmp_unit.h"
#include "pu/group_unit.h"

namespace SeqScan {
PatternUnitFactory::PatternUnitFactory(const ResMatcher& res_matcher, const ResMatcher& res_matcher_comp):
    res_matcher_(res_matcher),
    res_matcher_comp_(res_matcher_comp)
{}

std::unique_ptr<PatternUnit> PatternUnitFactory::CreateFromParseTree(const ParseTreeUnit *ptree)
{
  map<string, PatternUnit*> ref_map;
  return CreateFromNode(ptree, ref_map);
}

std::unique_ptr<PatternUnit> PatternUnitFactory::CreateFromNode(
    const ParseTreeUnit *node,
    map<string, PatternUnit *> &ref_map)
{
  std::unique_ptr<PatternUnit> tmp;
  PatternUnit* ref;
  switch (node->node_type_) {
    case ParseTreeUnit::UnitType::Sequence:
      if (node->suf_modifier_.mismatches_ == 0 &&
          node->suf_modifier_.insertions_ == 0 &&
          node->suf_modifier_.deletions_  == 0 &&
          node->suf_modifier_.indels_     == 0 &&
          node->suf_modifier_.edits_ == 0 ) {
        return std::unique_ptr<PatternUnit>(new KMPUnit(CreateModifiers(node), node->sequence_));
      }
      if (node->suf_modifier_.indels_ != 0 ) {
        return std::unique_ptr<PatternUnit>(new BacktrackIndelUnit(CreateModifiers(node), node->sequence_));
      }

      if (node->suf_modifier_.edits_ > 0 ) {
        return std::unique_ptr<PatternUnit>(new BacktrackEditsUnit(CreateModifiers(node), node->sequence_));
      }

      return std::unique_ptr<PatternUnit>(new BacktrackUnit(CreateModifiers(node), node->sequence_));
    case ParseTreeUnit::UnitType::Reference:
      ref = ref_map[node->referenced_label_];
      return std::unique_ptr<PatternUnit>(new ReferenceUnit(ref, CreateModifiers(node)));
    case ParseTreeUnit::UnitType::Composite:
      tmp = std::unique_ptr<PatternUnit>(new CompositeUnit(CreateModifiers(node)));
      for (size_t i = 0; i < node->children_.size(); ++i) {
        std::unique_ptr<PatternUnit> child_unit = CreateFromNode(node->children_[i], ref_map);
        ((CompositeUnit *) tmp.get())->AddUnit(child_unit);
      }
      break;
    case ParseTreeUnit::UnitType::Repeat:
      tmp = CreateFromNode(node->children_[0], ref_map);
      tmp = std::unique_ptr<PatternUnit>(new RepeatUnit(tmp,
                                                        CreateModifiers(node),
                                                        node->min_repeats_,
                                                        node->max_repeats_));
      break;
    case ParseTreeUnit::UnitType::Range:
      tmp = std::unique_ptr<PatternUnit>(new RangeUnit(CreateModifiers(node),
                                                       node->range_min_,
                                                       node->range_max_));
      break;
    case ParseTreeUnit::UnitType::Group:
      return std::unique_ptr<PatternUnit>(new GroupUnit(CreateModifiers(node),
                                                        node->sequence_,
                                                        node->pre_modifier_.hat_));
    default:
      throw "PatternUnitFactory: Unknown ParseTreeUnit type";
  }

  if (!node->label_.empty())
    ref_map[node->label_] = tmp.get();

  return tmp;
}

Modifiers PatternUnitFactory::CreateModifiers(const ParseTreeUnit *node) {
  const ResMatcher& rm = node->pre_modifier_.tilde_ ? res_matcher_comp_ : res_matcher_;

  return std::move(Modifiers(
      node->suf_modifier_.edits_,
      node->suf_modifier_.mismatches_,
      node->suf_modifier_.insertions_,
      node->suf_modifier_.deletions_,
      node->suf_modifier_.indels_,
      node->pre_modifier_.less_ ^ node->pre_modifier_.tilde_,  // reverse
      rm,
      node->label_));
}

}  // namespace SeqScan
