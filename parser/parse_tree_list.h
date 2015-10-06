#include <vector>
#include "parse_tree_unit.h"
using namespace std;

class ParseTreeList {
  public:
    ParseTreeList();
    void push_back(ParseTreeUnit* punit);
    ParseTreeUnit* get_parse_unit(int index);
    int get_size();
  private:
    vector<ParseTreeUnit*> patlist_;
};
