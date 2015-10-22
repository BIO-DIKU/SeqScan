#include "../src/pu/backtrack_unit.h"
#include "../src/modifiers.h"
#include "parse_tree_list.h"
#include <vector>
using namespace std;

vector<PatternUnit*> final_parse(ParseTreeList* plist) {
  vector<PatternUnit*> punits; 
  Modifiers mod = Modifiers::CreateMIDModifiers(1,2,0);
  PatternUnit* pu = new BacktrackUnit(mod, "TTGCAAAA");
  punits.push_back(pu);
  return punits;
}
