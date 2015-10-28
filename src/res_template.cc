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

#include "res_template.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

ResTemplate::ResTemplate(string matrix_file) :
  matrix_file_(matrix_file)
{
  FileMatrixToTemplate();
};

ResTemplate::ResTemplate(int matrix_num) :
  matrix_num_(matrix_num)
{
  MatrixToTemplate();
};

ResTemplate::~ResTemplate()
{};

void ResTemplate::set(size_t index) {
  res_template_.set(index, true);
}

bool ResTemplate::is_set(size_t index) {
  return res_template_.test(index);
}

void ResTemplate::FileMatrixToTemplate() {
  // TODO(Martin): implement this.
}

void ResTemplate::MatrixToTemplate() {
  switch (matrix_num_) {
    case 1:
      ParseMatrix(kMatrix1);
      break;
    case 2:
      ParseMatrix(kMatrix2);
      break;
    case 3:
      ParseMatrix(kMatrix3);
      break;
    case 4:
      ParseMatrix(kMatrix4);
      break;
    case 5:
      ParseMatrix(kMatrix5);
      break;
    case 6:
      ParseMatrix(kMatrix6);
      break;
    case 7:
      ParseMatrix(kMatrix7);
      break;
    case 8:
      ParseMatrix(kMatrix8);
      break;
    case 9:
      ParseMatrix(kMatrix9);
      break;
    case 10:
      ParseMatrix(kMatrix10);
      break;
    default:
      cerr << "Unknown matrix" << endl;  // TODO(Martin): Proper error handling.
      break;
  }
}

void ResTemplate::ParseMatrix(const string matrix_str) {
  istringstream matrix(matrix_str);
  string        seq1;

  while (!matrix.eof()) {
    string line;

    getline(matrix, line);

    if (line.empty()) {
      continue;
    }

    if (seq1.empty()) {
      seq1 = line;
      continue;
    }

    for (size_t i = 1; i < line.size(); ++i) {
      if (line[i] == '+') {
        res_template_.set(seq1[i] << kSizeOfChar | line[0], true);
      }
    }
  }
}
