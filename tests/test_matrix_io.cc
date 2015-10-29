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
#include "../src/matrix_io.h"

using namespace std;

TEST_CASE("MatrixIO w non-exiting file raises", "[matrix_io]") {
  string file = "matrix_file";
  vector<string> matrix;
  vector<string> matrix_comp;

  remove(file.c_str());

  REQUIRE_THROWS_AS(MatrixIO matrix_parse(file, matrix, matrix_comp), MatrixIOException);
}

TEST_CASE("MatrixIO w empty file raises", "[matrix_io]") {
  string file = "matrix_file";
  vector<string> matrix;
  vector<string> matrix_comp;

  ofstream output;
  output.open(file);
  output.close();

  REQUIRE_THROWS_AS(MatrixIO matrix_parse(file, matrix, matrix_comp), MatrixIOException);

  remove(file.c_str());
}

TEST_CASE("MatrixIO w one matrix in a file parses OK", "[matrix_io]") {
  string file = "matrix_file";
  vector<string> matrix;
  vector<string> matrix_comp;

  ofstream output;
  output.open(file);
  output << " AC" << endl;
  output << "A+ " << endl;
  output << "C +" << endl;
  output.close();

  MatrixIO matrix_parse(file, matrix, matrix_comp);

  string m1;
  string m2;

  for (auto it : matrix) {
    m1 += it;
  }

  for (auto it : matrix_comp) {
    m2 += it;
  }

  REQUIRE(m1 == " ACA+ C +");
  REQUIRE(m2 == "");

  remove(file.c_str());
}

TEST_CASE("MatrixIO w two matrices in a file parses OK", "[matrix_io]") {
  string file = "matrix_file";
  vector<string> matrix;
  vector<string> matrix_comp;

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

  MatrixIO matrix_parse(file, matrix, matrix_comp);

  string m1;
  string m2;

  for (auto it : matrix) {
    m1 += it;
  }

  for (auto it : matrix_comp) {
    m2 += it;
  }

  REQUIRE(m1 == " ACA+ C +");
  REQUIRE(m2 == "~ACA +C+ ");

  remove(file.c_str());
}
