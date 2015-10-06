//#include "parse_tree_unit.h"
#include "parse_tree_list.h"
#include <cstdio>
#include <iostream>
using namespace std;

ParseTreeUnit::ParseTreeUnit() {  
  is_backtrack_ = false;
  is_range_ = false;
  is_composite_ = false;
  is_labeled_ = false;
  is_reference_ = false;
  is_or_ = false;
  is_matchgroup_ = false;
  sequence_ = "";
  mis_ = 0;
  ins_ = 0;
  del_ = 0;
  indel_ = 0;
  edits_ = 0;
  min_repeats_ = 0;
  max_repeats_ = 0;
  range_min_ = 0;
  range_max_ = 0;
  reverse_ = false;
  complement_ = false;
  greedy_ = false;
  rep_open_ = false;
  group_not_ = false;
  group_greedy_ = false;
  group_ = "";
  composite_ = new ParseTreeList();
}

void ParseTreeUnit::init_or_units() {
  ParseTreeUnit* or_units_[2];
}

void ParseTreeUnit::insert_or_units(ParseTreeUnit* p1, ParseTreeUnit* p2) {
  or_units_[0] = p1;
  or_units_[1] = p2;
}

void ParseTreeUnit::pprint() {
  printf("**********************PARSE TREE UNIT**********************\n");
  printf(" is_backtrack %d\n is_range     %d\n is_composite %d\n", is_backtrack_, is_range_, is_composite_);
  printf(" is_labeled   %d\n is_reference %d\n is_or        %d\n", is_labeled_, is_reference_, is_or_);
  printf(" is_matchgroup%d\n group_not_   %d\n group_greedy %d\n", is_matchgroup_, group_not_, group_greedy_);
  printf(" mis:         %d\n ins:         %d\n del:         %d\n", mis_, ins_, del_);
  printf(" indels:      %d\n edits:       %d\n min_repeats: %d\n", indel_, edits_, min_repeats_);
  printf(" max_repeats: %d\n label:       %s\n reverse:     %d\n", max_repeats_, "", reverse_);
  printf(" complement:  %d\n greedy:      %d\n rep_open:    %d\n\n", complement_, greedy_, rep_open_);
  if (is_reference_) {
    printf("_______________________REFERENCE____________________\n");
    reference_->pprint();
    printf("____________________REFERENCE_END___________________\n");
  }
  if (is_or_) {
    printf("~~~~~~~~~~~~~~~~~~~~~~OR~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    or_units_[0]->pprint();
    or_units_[1]->pprint();
    printf("~~~~~~~~~~~~~~~~~~~~~~OR_END~~~~~~~~~~~~~~~~~~~~~~~~\n");
  } 
  if (is_composite_) {
    printf("----------------------COMP--------------------------\n");
    for (int i = 0; i < composite_->get_size(); i++) {
      composite_->get_parse_unit(i)->pprint();
    }
    printf("----------------------COMP_END---------------------------\n");
  }
}





