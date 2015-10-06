#include <string>
#include <vector>
using namespace std;

class ParseTreeList;

class ParseTreeUnit {
  public:
    ParseTreeUnit();
    bool is_backtrack_;
    bool is_range_;
    bool is_composite_;
    bool is_labeled_;
    bool is_reference_;
    bool is_or_;
    bool is_matchgroup_;
    string sequence_;

    int mis_;
    int ins_;
    int del_;
    int indel_;
    int edits_;

    int min_repeats_;
    int max_repeats_;
    bool rep_open_;
    bool greedy_;

    int range_min_;
    int range_max_;

    bool reverse_;
    bool complement_;

    bool group_not_;
    bool group_greedy_;
    string group_;

    ParseTreeUnit* reference_;
    ParseTreeList* composite_;
    ParseTreeUnit* or_units_[2];

    void init_or_units();
    void insert_or_units(ParseTreeUnit* p1, ParseTreeUnit* p2);
    void pprint();
};


