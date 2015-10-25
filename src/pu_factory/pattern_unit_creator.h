//
// Created by Rasmus Fonseca on 25/10/15.
//

#ifndef SEQSCAN_PATTERN_UNIT_CREATOR_H
#define SEQSCAN_PATTERN_UNIT_CREATOR_H

#include <map>
#include <string>

#include <ptnode.h>

#include "pu/pattern_unit.h"
#include "modifiers.h"

namespace SeqScan {

  using ::std::string;
  using ::std::map;

  class PatternUnitCreator {
   public:
    std::unique_ptr<PatternUnit> create_from_parse_tree(const PTNode *ptree);

   private:
    std::unique_ptr<PatternUnit> create_from_node(const PTNode *node, map<string,PatternUnit*> &ref_map);

    Modifiers create_modifiers(const PTNode* node);

  };

} // namespace SeqScan

#endif //SEQSCAN_PATTERN_UNIT_CREATOR_H
