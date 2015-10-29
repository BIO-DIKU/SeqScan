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

#include "pattern_io.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

PatternIO::PatternIO(string pat_file, vector<string> &patterns) :
  pat_file_(pat_file),
  patterns_(patterns)
{
  Parse();
  CheckPatterns();
}

PatternIO::~PatternIO()
{}

void PatternIO::Parse() {
  ifstream input(pat_file_);
  string   line;

  if (!input.good()) {
    string msg = "Error: File not found or readable: " + pat_file_;
    throw PatternIOException(msg);
  }

  while (getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    patterns_.push_back(line);
  }

  input.close();
}

void PatternIO::CheckPatterns() {
  if (!patterns_.empty()) {
    return;
  }

  string msg = "Error: No patterns in file: " + pat_file_;
  throw PatternIOException(msg);
}
