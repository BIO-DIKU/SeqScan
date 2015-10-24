#include "parse_tree_list.h"
#include "final_parser.h"

bool check_edits(ParseTreeUnit* pu, int pu_no);
bool check_range(ParseTreeUnit* pu, int pu_no);
bool check_composite(ParseTreeUnit* pu, int pu_no);
bool check_labeled(ParseTreeUnit* pu, int pu_no);
bool check_reference(ParseTreeUnit* pu, int pu_no);
bool check_or(ParseTreeUnit* pu, int pu_no);
bool check_matchgroup(ParseTreeUnit* pu, int pu_no);


int check_sanity(ParseTreeList* plist);
