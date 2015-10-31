//
// Created by Rasmus Fonseca on 25/10/15.
//

#ifndef SEQSCAN_PATTERN_UNIT_CREATOR_H_
#define SEQSCAN_PATTERN_UNIT_CREATOR_H_

#include <map>
#include <string>

#include <parser/parse_tree_unit.h>

#include "pu/pattern_unit.h"
#include "modifiers.h"
#include "res_matcher.h"

namespace SeqScan {

  using ::std::string;
  using ::std::map;

  class PatternUnitCreator {
   public:
    PatternUnitCreator(const ResMatcher& res_matcher, const ResMatcher& res_matcher_comp);

    std::unique_ptr<PatternUnit> create_from_parse_tree(const ParseTreeUnit *ptree);

   private:
    std::unique_ptr<PatternUnit> create_from_node(const ParseTreeUnit *node, map<string,PatternUnit*> &ref_map);

    Modifiers create_modifiers(const ParseTreeUnit* node);

    const ResMatcher& res_matcher_;
    const ResMatcher& res_matcher_comp_;

  };

} // namespace SeqScan

#endif  // SEQSCAN_PATTERN_UNIT_CREATOR_H_
