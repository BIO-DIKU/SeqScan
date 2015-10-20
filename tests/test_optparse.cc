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
  int  argc     = 0;
  char* argv[0] = {};

  REQUIRE_THROWS_AS(OptParse opt_parse(argc, argv), OptParseException);
}

TEST_CASE("OptParse have correct default option values", "[optparse]") {
  int   argc    = 1;
  const char* argv[] = {"file"};

  OptParse opt_parse(argc, (char **)argv);

  REQUIRE(opt_parse.options_.help            == false);
  REQUIRE(opt_parse.options_.complement      == OptParse::OptComplement::Forward);
  REQUIRE(opt_parse.options_.direction       == OptParse::OptDirection::Forward);
  REQUIRE(opt_parse.options_.threads         == 1);
  REQUIRE(opt_parse.options_.score_encoding  == OptParse::OptScoreEncoding::Phred33);
  REQUIRE(opt_parse.options_.score_min       == 25);
  REQUIRE(opt_parse.options_.ambiguate       == false);
  REQUIRE(opt_parse.options_.match_type      == 1);
  REQUIRE(opt_parse.options_.overlap         == false);
  REQUIRE(opt_parse.options_.version         == false);
  REQUIRE(opt_parse.options_.verbose         == false);
}

TEST_CASE("OptParse help", "[optparse]") {
  int argc = 1;

  SECTION("short option can be set OK") {
    const char* argv[1] = {"-h"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.help);
  }

  SECTION("long option can be set OK") {
    const char* argv[1] = {"--help"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.help);
  }
}

// TEST_CASE("OptParse long options can be set OK", "[optparse]") {
// }

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
// TEST_CASE("OptParse w grouped short options can be set OK") {
// }
//
// TEST_CASE("OptParse w pattern_file and non-existing file raises", "[optparse]") {
// }
//
// TEST_CASE("OptParse w match_file and non-existing file raises", "[optparse]") {
// }
