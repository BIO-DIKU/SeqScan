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

#include "parse_tree_list.h"

#include <cstdio>
#include <iostream>

using namespace std;

ParseTreeUnit::ParseTreeUnit() {
  type_          = 0;
  reverse_       = false;
  complement_    = false;
  non_greedy_    = false;
  rep_open_      = false;
  group_not_     = false;
  group_greedy_  = false;
  start_anchor_  = false;
  end_anchor_    = false;
  group_         = "";
  sequence_      = "";
  mis_           = 0;
  ins_           = 0;
  del_           = 0;
  indel_         = 0;
  edits_         = 0;
  min_repeats_   = 0;
  max_repeats_   = 0;
  range_min_     = 0;
  range_max_     = 0;
  composite_     = new ParseTreeList();
}

void ParseTreeUnit::init_or_units() {
  ParseTreeUnit* or_units_[2];
}

void ParseTreeUnit::insert_or_units(ParseTreeUnit* p1, ParseTreeUnit* p2) {
  or_units_[0] = p1;
  or_units_[1] = p2;
}

void ParseTreeUnit::pprint() {
  printf("**********************PARSE TREE UNIT**********************\n");
  printf(" type:        %d\n group_not_   %d\n group_greedy %d\n", type_, group_not_, group_greedy_);
  printf(" mis:         %d\n ins:         %d\n del:         %d\n", mis_, ins_, del_);
  printf(" indels:      %d\n edits:       %d\n min_repeats: %d\n", indel_, edits_, min_repeats_);
  printf(" max_repeats: %d\n label:       %s\n reverse:     %d\n", max_repeats_, "", reverse_);
  printf(" complement:  %d\n non_greedy:  %d\n rep_open:    %d\n\n", complement_, non_greedy_, rep_open_);
  printf(" start_anchor:%d\n end_anchor:  %d\n", start_anchor_, end_anchor_);

  if (type_ == 5) {
    printf("_______________________REFERENCE____________________\n");
    reference_->pprint();
    printf("____________________REFERENCE_END___________________\n");
  }

  if (type_ == 6) {
    printf("~~~~~~~~~~~~~~~~~~~~~~OR~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    or_units_[0]->pprint();
    or_units_[1]->pprint();
    printf("~~~~~~~~~~~~~~~~~~~~~~OR_END~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }

  if (type_ == 3) {
    printf("----------------------COMP--------------------------\n");

    for (int i = 0; i < composite_->get_size(); i++) {
      composite_->get_parse_unit(i)->pprint();
    }

    printf("----------------------COMP_END---------------------------\n");
  }
}
