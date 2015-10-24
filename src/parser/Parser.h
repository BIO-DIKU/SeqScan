//
// Created by Rasmus Fonseca on 22/10/15.
//

#ifndef SEQSCAN_PARSER_H
#define SEQSCAN_PARSER_H

#include <string>
#include <iostream>

#include "../pu/pattern_unit.h"
#include "parse_tree_unit.h"
#include "parse_tree_list.h"
#include "seq_par.tab.hh"

class Parser {
public:
  Parser();

  std::unique_ptr<PatternUnit> parse(std::string raw_pattern);

private:
  PatternUnit* final_parse(ParseTreeList* plist);
  ParseTreeList* first_parse(std::string raw_pattern);
};


#endif //SEQSCAN_PARSER_H
