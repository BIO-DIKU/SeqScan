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


#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include "catch.h"
#include "../src/res_matcher.h"

using namespace std;

TEST_CASE("ResMatcher returns correctly", "[res_matcher]") {
  ResMatcher res_matcher(8);

  SECTION("w identical residues is OK") {
    REQUIRE(res_matcher.Match('A', 'A'));
  }

  SECTION("w matching residue pair is OK") {
    REQUIRE(res_matcher.Match('T', 'U'));
  }

  SECTION("w matching ambiguity is OK") {
    REQUIRE(res_matcher.Match('T', 'N'));
  }

  SECTION("w/o matching residue pair is bad") {
    REQUIRE_FALSE(res_matcher.Match('A', 'T'));
  }
}

TEST_CASE("ResMatcher::FileMatrixToMatcher", "[res_matcher]") {
  string file = "matrix_file";
  vector<string> matrix;
  vector<string> matrix_comp;

  remove(file.c_str());

  ofstream output;
  output.open(file);
  output << " AC" << endl;
  output << "A+ " << endl;
  output << "C +" << endl;
  output << endl;
  output << "~AT" << endl;
  output << "A +" << endl;
  output << "T+ " << endl;
  output.close();

  ResMatcher res_matcher(file);
  ResMatcher res_matcher_comp(file, true);

  SECTION("Parse of forward matrix OK") {
    REQUIRE(res_matcher.Match('A', 'A'));
    REQUIRE(res_matcher.Match('C', 'C'));
  }

  SECTION("Parse of complement matrix OK") {
    REQUIRE(res_matcher_comp.Match('T', 'A'));
    REQUIRE(res_matcher_comp.Match('A', 'T'));
  }

  remove(file.c_str());
}

TEST_CASE("ResMatcher::MatrixToMatcher all matrices can be loaded OK", "[res_matcher]") {
  vector<int> matrices = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, 10};

  for (int i : matrices) {
    REQUIRE_NOTHROW(ResMatcher res_matcher(i));
  }
}

