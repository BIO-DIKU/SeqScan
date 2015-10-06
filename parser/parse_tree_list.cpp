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
#include <vector>

using namespace std;

ParseTreeList::ParseTreeList() {}

int ParseTreeList::get_size() {
  return patlist_.size();
}

void ParseTreeList::push_back(ParseTreeUnit* panit) {
  patlist_.push_back(panit);
}

ParseTreeUnit* ParseTreeList::get_parse_unit(int index) {
  return patlist_[index];
}
