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
#include "pattern_io.h"

int main(int argc, char *argv[]) {
  std::vector<std::string> patterns;

  OptParse opt_parse(argc, (char**)argv);

  if (!opt_parse.options_.pattern_file.empty()) {
    PatternIO pat_parse(opt_parse.options_.pattern_file, patterns);
  } else {
    patterns.push_back(opt_parse.options_.pattern);
  }

  if (opt_parse.options_.verbose) {
    opt_parse.PrintVersion();
    std::cerr << std::endl;
    opt_parse.PrintCommandLine();
    std::cerr << std::endl << std::endl;
    opt_parse.PrintOptions();

    std::cerr << std::endl << "Patterns:" << std::endl;

    for (auto it : patterns) {
      std::cerr << "  " << it << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
