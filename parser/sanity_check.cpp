#include "parse_tree_list.h"
#include "final_parser.h"
#include <cstdio>
#include <iostream>
using namespace std;

bool check_edits(ParseTreeUnit* pu, int pu_no) {
  int seq_len = pu->sequence_.length();
  if (pu->mis_ + pu->indel_ + pu->del_ >= seq_len) {
    cout << "WARNING (Sanity check): Pattern Unit " << pu_no + 1 << " may match sequence of length 0\n";
  }
  if (pu->del_ > seq_len) {
    pu->del_ = seq_len;
  }
  if (pu->mis_ > seq_len) {
    pu->mis_ = seq_len;
  }
  return true;
}

bool check_range(ParseTreeUnit* pu, int pu_no) {
  ;
}

bool check_composite(ParseTreeUnit* pu, int pu_no) {
  ;
}

bool check_labeled(ParseTreeUnit* pu, int pu_no) {
  ;
}

bool check_reference(ParseTreeUnit* pu, int pu_no) {
  ;
}

bool check_or(ParseTreeUnit* pu, int pu_no) {
  ;
}

bool check_matchgroup(ParseTreeUnit* pu, int pu_no) {
  ;
}

int check_unit(ParseTreeUnit* pu, int pu_no) {
  switch (pu->type_) {
    case 1:
      check_edits(pu, pu_no);
    case 2:
      check_range(pu, pu_no);
    case 3:
      check_composite(pu, pu_no);
    case 4:
      check_labeled(pu, pu_no);
    case 5:
      check_reference(pu, pu_no);
    case 6:
      check_or(pu, pu_no);
    case 7:
      check_matchgroup(pu, pu_no);
    default:
      cout << "Unknown ParseTreeUnit type: " << pu->type_ << "\n";
  }
}


int check_sanity(ParseTreeList* plist) {
  ParseTreeUnit* pu;
  for (int i = 0; i < plist->get_size(); i++) {
    pu = plist->get_parse_unit(i);
    check_unit(pu, i);
  }
  final_parse(plist);
}
