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

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "catch.h"
#include "../src/pattern_io.h"

using namespace std;

TEST_CASE("PatternIO w non-exiting file raises", "[pattern_io]") {
  string file = "pat_file";
  vector<string> patterns;

  REQUIRE_THROWS_AS(PatternIO pat_parse(file, patterns), PatternIOException);
}

TEST_CASE("PatternIO w empty file raises", "[pattern_io]") {
  string file = "pat_file";
  vector<string> patterns;

  ofstream output;
  output.open(file);
  output.close();

  REQUIRE_THROWS_AS(PatternIO pat_parse(file, patterns), PatternIOException);

  remove(file.c_str());
}

TEST_CASE("PatternIO w OK file parses OK", "[pattern_io]") {
  string file = "pat_file";
  vector<string> patterns;

  ofstream output;
  output.open(file);
  output << "p1=ATC" << endl;
  output << "" << endl;
  output << "ATG ... TGA" << endl;
  output.close();

  PatternIO pat_parse(file, patterns);

  REQUIRE(patterns.front() == "p1=ATC");
  REQUIRE(patterns.back() == "ATG ... TGA");

  remove(file.c_str());
}
