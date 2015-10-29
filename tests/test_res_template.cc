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
#include "../src/res_template.h"

using namespace std;

TEST_CASE("ResTemplate::FileMatrixToTemplate", "[res_template]") {
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
  output << "~AC" << endl;
  output << "A +" << endl;
  output << "C+ " << endl;
  output.close();

  ResTemplate res_template(file);
  ResTemplate res_template_comp(file, true);

  SECTION("Parse of forward matrix OK") {
    REQUIRE(res_template.is_set('A' << kSizeOfChar | 'A'));
    REQUIRE(res_template.is_set('C' << kSizeOfChar | 'C'));
  }

  SECTION("Parse of complement matrix OK") {
    REQUIRE(res_template_comp.is_set('A' << kSizeOfChar | 'C'));
    REQUIRE(res_template_comp.is_set('C' << kSizeOfChar | 'A'));
  }

  remove(file.c_str());
}

TEST_CASE("ResTemplate::MatrixToTemplate all matrices can be loaded OK", "[res_template]") {
  vector<int> matrices = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, 10};

  for (int i : matrices) {
    REQUIRE_NOTHROW(ResTemplate res_template(i));
  }
}

TEST_CASE("ResTemplate::MatrixToTemplate is_set() works OK", "[res_template]") {
  ResTemplate res_template(8);

  REQUIRE(res_template.is_set('A' << kSizeOfChar | 'N'));
  REQUIRE(res_template.is_set('N' << kSizeOfChar | 'A'));
}
