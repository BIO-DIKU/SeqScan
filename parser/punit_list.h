#include <vector>
#include "../src/pu/pattern_unit.h"
using namespace std;

class PunitList {
  public:
    PunitList();
    void push_back(PatternUnit* punit);
    PatternUnit* get_punit(int index);
    int get_size();
  private:
    vector<PatternUnit*> patlist_;
};
