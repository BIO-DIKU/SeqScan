#include "parse_tree_list.h"
#include "parse_tree_unit.h"
#include "seq_par.tab.h"
#include <iostream>
using namespace std;

extern ParseTreeList* parse(string s);

int main() {
  string s = "ATT/2,3,4 GGGGG{4,6}";
  ParseTreeList* par_list = parse(s);
  for (int i = 0; i < par_list->get_size(); i++) {
    ParseTreeUnit* x = par_list->get_parse_unit(i);
    par_list->get_parse_unit(i)->pprint();
  }
  return 1;
}
