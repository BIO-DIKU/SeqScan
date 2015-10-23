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

#include <stdio.h>
#include "optparse.h"
// #include "pattern_io.h"
// #include "match_matrix.h"
// #include "match_matrix_io.h"

int main(int argc, char *argv[]) {
  // std::vector<std::string> patterns;
  // MatchMatrix match_matrix;
  //
  OptParse opt_parse(argc, (char**)argv);

  if (opt_parse.options_.verbose) {
    opt_parse.PrintVersion();
    opt_parse.PrintCommandLine();
    std::cout << std::endl;
    opt_parse.PrintOptions();
  }

  // if (opt_parse.pattern_file) {
  //   PatternIO.parse(const &opt_parse.pattern_file, patterns);
  // } else {
  //   patterns.push_back(opt_parse.pattern);
  // }
  //
  // if (opt_parse.match_file) {
  //   MatchMatrixIO.parse(const &opt_parse.match_file, match_matrix);
  // } else {
  //   match_matrix.generate(opt_parse.match_matrix);
  // }

  return EXIT_SUCCESS;
}
