#include "parse_tree_list.h"
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

ParseTreeList::ParseTreeList() {
  ;
}

int ParseTreeList::get_size() {
  return patlist_.size();
}
void ParseTreeList::push_back(ParseTreeUnit* panit) {
  patlist_.push_back(panit);
}

ParseTreeUnit* ParseTreeList::get_parse_unit(int index) {
  return patlist_[index];
}
