//
// Created by Rasmus Fonseca on 25/10/15.
//

#include "pattern_unit_creator.h"

#include "pu/backtrack_unit.h"
#include "pu/reference_unit.h"
#include "pu/composite_unit.h"
#include "pu/repeat_unit.h"
#include "pu/range_unit.h"

namespace SeqScan{

  std::unique_ptr<PatternUnit> PatternUnitCreator::create_from_parse_tree(const ParseTreeUnit *ptree)
  {
    map<string,PatternUnit*> ref_map;
    return create_from_node(ptree, ref_map);
  }


  std::unique_ptr<PatternUnit> PatternUnitCreator::create_from_node(
      const ParseTreeUnit *node, 
      map<string,PatternUnit*> &ref_map) 
  {

    std::unique_ptr<PatternUnit> tmp;
    PatternUnit* ref;
    switch (node->node_type_) {
      case ParseTreeUnit::UnitType::Sequence:
        return std::unique_ptr<PatternUnit>(new BacktrackUnit(create_modifiers(node), node->sequence_));
      case ParseTreeUnit::UnitType::Reference:
        ref = ref_map[node->referenced_label_];
        return std::unique_ptr<PatternUnit>(new ReferenceUnit(ref, create_modifiers(node)));
      case ParseTreeUnit::UnitType::Composite:
        tmp = std::unique_ptr<PatternUnit>(new CompositeUnit(create_modifiers(node)));
        for (size_t i = 0; i < node->children_.size(); ++i) {
          std::unique_ptr<PatternUnit> child_unit = create_from_node(node->children_[i], ref_map);
          ((CompositeUnit *) tmp.get())->AddUnit(child_unit);
        }
        break;
      case ParseTreeUnit::UnitType::Repeat:
        tmp = create_from_node(node->children_[0], ref_map);
        tmp = std::unique_ptr<PatternUnit>(new RepeatUnit(tmp,
                                                          create_modifiers(node),
                                                          node->min_repeats_,
                                                          node->max_repeats_));
        break;
      case ParseTreeUnit::UnitType::Range:
        tmp = std::unique_ptr<PatternUnit>(new RangeUnit(create_modifiers(node),
                                                          node->range_min_,
                                                          node->range_max_));
        break;
      default:
        throw "PatternUnitCreator: Unknown ParseTreeUnit type";
    }

    if (!node->label_.empty())
      ref_map[node->label_] = tmp.get();

    return tmp;

  }

  Modifiers PatternUnitCreator::create_modifiers(const ParseTreeUnit* node)
  {
    return std::move(Modifiers(
        node->suf_modifier_.errors_,
        node->suf_modifier_.mismatches_,
        node->suf_modifier_.insertions_,
        node->suf_modifier_.deletions_,
        node->suf_modifier_.indels_,
        node->pre_modifier_.less_ ^ node->pre_modifier_.tilde_, //reverse
        node->pre_modifier_.tilde_,  //complement
        true,
        node->label_
    ));
  }

} // namespace SeqScan
