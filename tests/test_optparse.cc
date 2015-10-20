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

#include <string>

#include "catch.h"
#include "../src/optparse.h"

using namespace std;

TEST_CASE("OptParse w/o input file(s) raises", "[optparse]") {
  int  argc      = 0;
  char argv[]    = "";
  char *argv_ptr = argv;

//  OptParse options(argc, &argv_ptr);

//  options.PrintOptions();
}

// TEST_CASE("OptParse w/o pattern or pattern_file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse w pattern and pattern_file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse w match_type and match_file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse w complement option", "[optparse]") {
//   SECTION("forward value OK") {
//     REQUIRE(long_options[] == "forward");
//   }
//
//   SECTION("reverse value OK") {
//     REQUIRE(long_options[] == "reverse");
//   }
//
//   SECTION("both value OK") {
//     REQUIRE(long_options[] == "both");
//   }
//
//   SECTION("bad value raises") {
//   }
// }
//
// TEST_CASE("OptParse w direction option", "[optparse]") {
//   SECTION("forward value OK") {
//     REQUIRE(long_options[] == "forward");
//   }
//
//   SECTION("reverse value OK") {
//     REQUIRE(long_options[] == "reverse");
//   }
//
//   SECTION("bad value raises") {
//   }
// }
//
// TEST_CASE("OptParse w score_encoding option", "[optparse]") {
//   SECTION("Phred33 value OK") {
//     REQUIRE(long_options[] == "Phread33");
//   }
//
//   SECTION("Phred64 value OK") {
//     REQUIRE(long_options[] == "Phread64");
//   }
//
//   SECTION("bad value raises") {
//   }
// }
//
// TEST_CASE("OptParse w pattern_file and non-existing file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse w match_file and non-existing file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse have correct default option values", "[optparse]") {
// }
//
// TEST_CASE("OptParse short options can be set OK", "[optparse]") {
//   char argv = "-p ATC"
// }
//
// TEST_CASE("OptParse long options can be set OK", "[optparse]") {
// }
