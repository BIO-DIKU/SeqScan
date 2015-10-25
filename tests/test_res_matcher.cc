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

#include "catch.h"
#include "../src/res_matcher.h"
#include <vector>

using namespace std;

TEST_CASE("ResMatcher returns correctly", "[res_matcher]") {
  vector<string> match_pairs = {"AA", "TU"};
  ResTemplate    res_template(match_pairs);
  ResMatcher     res_matcher(res_template);

  SECTION("w identical residues") {
    REQUIRE(res_matcher.match("A", "A"));
  }

  SECTION("w matching residue pair") {
    REQUIRE(res_matcher.match("T", "U"));
  }

  SECTION("w/o matching residue pair") {
    REQUIRE_FALSE(res_matcher.match("A", "T"));
  }
}
