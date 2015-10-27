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

  std::unique_ptr<PatternUnit> PatternUnitCreator::create_from_parse_tree(const PTNode *ptree)
  {
    map<string,PatternUnit*> ref_map;
    return create_from_node(ptree, ref_map);
  }


  std::unique_ptr<PatternUnit> PatternUnitCreator::create_from_node(
      const PTNode *node,
      map<string,PatternUnit*> &ref_map)
  {


    std::unique_ptr<PatternUnit> tmp;
    PatternUnit* ref;
    switch (node->node_type_) {
      case PTNode::kSequence:
        tmp = std::unique_ptr<PatternUnit>(new BacktrackUnit(create_modifiers(node), node->sequence_));
        break;
      case PTNode::kReference:
        ref = ref_map[node->referenced_label_];
        tmp = std::unique_ptr<PatternUnit>(new ReferenceUnit(ref, create_modifiers(node)));
        break;
      case PTNode::kComposite:
        tmp = std::unique_ptr<PatternUnit>(new CompositeUnit(create_modifiers(node)));
        for (size_t i = 0; i < node->children_.size(); ++i) {
          std::unique_ptr<PatternUnit> child_unit = create_from_node(node->children_[i], ref_map);
          ((CompositeUnit *) tmp.get())->AddUnit(child_unit);
        }
        break;
      case PTNode::kRepeat:
        tmp = create_from_node(node->children_[0], ref_map);
        tmp = std::unique_ptr<PatternUnit>(new RepeatUnit(tmp,
                                                          create_modifiers(node),
                                                          node->min_repeats_,
                                                          node->max_repeats_));
        break;
      case PTNode::kRange:
        tmp = std::unique_ptr<PatternUnit>(new RangeUnit(create_modifiers(node),
                                                          node->min_range_,
                                                          node->max_range_));
        break;
      default:
        throw "PatternUnitCreator: Unknown PTNode type";
    }

    if (!node->label_.empty())
      ref_map[node->label_] = tmp.get();

    return tmp;

  }

  Modifiers PatternUnitCreator::create_modifiers(const PTNode* node)
  {
    return std::move(Modifiers(
        node->modifier_.errors_,
        node->modifier_.mismatches_,
        node->modifier_.insertions_,
        node->modifier_.deletions_,
        node->modifier_.indels_,
        node->pre_modifier_.reverse_,
        node->pre_modifier_.complement_,
        true,
        node->label_
    ));
  }

} // namespace SeqScan