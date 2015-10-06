#include "punit_list.h"
#include <vector>
#include "../src/pu/pattern_unit.h"
using namespace std;

PunitList::PunitList() {
  ;
}

void PunitList::push_back(PatternUnit* punit) {
  patlist_.push_back(punit);
}

PatternUnit* PunitList::get_punit(int index) {
  return patlist_[index];
}

int PunitList::get_size() {
  return patlist_.size();
}
