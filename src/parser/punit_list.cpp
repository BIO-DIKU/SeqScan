#include "punit_list.h"
#include <vector>
#include "../pu/pattern_unit.h"
using namespace std;

PunitList::PunitList() {
  ;
}

void PunitList::push_back(PatternUnit* punit) {
  patlist.push_back(punit);
}

PatternUnit* PunitList::get_punit(int index) {
  return patlist[index];
}

int PunitList::get_size() {
  return patlist.size();
}
