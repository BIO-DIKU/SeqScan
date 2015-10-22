/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */
#ifndef PARSE_TREE_UNIT_H_
#define PARSE_TREE_UNIT_H_

#include <string>
#include <vector>
using namespace std;

class ParseTreeList;

/* Attribute "type" indicates the type of pattern unit
   1: Backtrack
   2: Range
   3: Composite
   4: Labeled
   5: Reference
   6: Or
   7: Matchgroup
 */
class ParseTreeUnit {
  public:
    ParseTreeUnit();
    string sequence_;
    int type_;

    int mis_;
    int ins_;
    int del_;
    int indel_;
    int edits_;

    int min_repeats_;
    int max_repeats_;
    bool rep_open_;
    bool non_greedy_;

    int range_min_;
    int range_max_;

    bool reverse_;
    bool complement_;

    bool group_not_;
    bool group_greedy_;
    string group_;

    bool start_anchor_;
    bool end_anchor_;

    ParseTreeUnit* reference_;
    ParseTreeList* composite_;
    ParseTreeUnit* or_units_[2];

    void init_or_units();
    void insert_or_units(ParseTreeUnit* p1, ParseTreeUnit* p2);
    void pprint();
};

#endif
