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

#include "matrix_io.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

MatrixIO::MatrixIO(string         matrix_file,
                   vector<string> &matrix,
                   bool           matrix_comp) :
  matrix_file_(matrix_file),
  matrix_(matrix),
  matrix_comp_(matrix_comp)
{
  Parse();
  CheckMatrices();
}

MatrixIO::~MatrixIO()
{}

string MatrixIO::ToString() {
  string str;

  for (auto it : matrix_) {
    str += it + "\n";  // TODO(Martin): replace with platform independant var.
  }

  return str;
}

void MatrixIO::Parse() {
  ifstream input(matrix_file_);
  string   line;
  bool     comp = false;

  if (!input.good()) {
    string msg = "Error: Matrix file not found or readable: " + matrix_file_;
    throw MatrixIOException(msg);
  }

  while (getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    if (line[0] == '~') {
      if (!matrix_comp_) {
        break;
      }
      comp = true;
    }

    if (matrix_comp_ && comp) {
      matrix_.push_back(line);
    }

    if (!matrix_comp_ && !comp) {
      matrix_.push_back(line);
    }
  }

  input.close();
}

void MatrixIO::CheckMatrices() {
  if (!matrix_.empty()) {
    return;
  }

  string msg = "Error: No data in matrix: " + matrix_file_;
  throw MatrixIOException(msg);
}
