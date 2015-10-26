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

ResTemplate::ResTemplate(string template_file) :
  template_file_(template_file)
{
  FileMatrixToTemplate();
};

ResTemplate::ResTemplate(int template_num) :
  template_num_(template_num)
{
  MatrixToTemplate();
};

ResTemplate::ResTemplate(vector<string> match_pairs) :
  res_template_(),
  match_pairs_(match_pairs)
{
  MatchPairsToTemplate();
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

// TODO(Martin): Allow chosing of matrix.
void ResTemplate::MatrixToTemplate() {
  switch (template_num_) {
    case 1:
      istringstream matrix(kTemplate1);
      break;
  }

  istringstream matrix(kTemplate1);
  bool first = true;
  string seq1;

  while (!matrix.eof()) {
    string line;

    if (first) {
      getline(matrix, seq1); // TODO(Someone): fix nasty hack to advance a line.
      getline(matrix, seq1);
      first = false;
    } else {
      getline(matrix, line);

      for (size_t i = 1; i < line.size(); ++i) {
        if (line[i] == 'x') {
          res_template_.set(seq1[0 + 1] << kSizeOfChar | line[0], true);
        }
      }
    }
  }
}

void ResTemplate::MatchPairsToTemplate() {
  for (auto it : match_pairs_) {
    res_template_.set(it[0] << kSizeOfChar | it[1], true);
  }
}
