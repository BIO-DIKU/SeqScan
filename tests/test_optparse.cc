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

// TEST_CASE("OptParse w/o arguments sets help option", "[optparse]") {
//   int   argc         = 1;
//   const char *argv[] = {"seqscan"};
//
//   REQUIRE_THROWS_AS(OptParse opt_parse(argc, (char**)argv), OptParseException);
// }

TEST_CASE("OptParse have correct default option values", "[optparse]") {
  int   argc         = 1;
  const char* argv[] = {"seqscan"};

  OptParse opt_parse(argc, (char **)argv);

  REQUIRE(opt_parse.options_.help           == false);
  REQUIRE(opt_parse.options_.complement     == OptParse::OptComplement::Forward);
  REQUIRE(opt_parse.options_.direction      == OptParse::OptDirection::Forward);
  REQUIRE(opt_parse.options_.threads        == 1);
  REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred33);
  REQUIRE(opt_parse.options_.score_min      == 25);
  REQUIRE(opt_parse.options_.ambiguate      == false);
  REQUIRE(opt_parse.options_.match_type     == 1);
  REQUIRE(opt_parse.options_.overlap        == false);
  REQUIRE(opt_parse.options_.version        == false);
  REQUIRE(opt_parse.options_.verbose        == false);
}

TEST_CASE("OptParse help", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 2;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-h"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.help);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--help"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.help);
  }
}

TEST_CASE("OptParse pattern", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.pattern == "ATC");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--pattern", "ATC"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.pattern == "ATC");
  }
}

TEST_CASE("OptParse pattern_file", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-P", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.pattern_file == "file");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--pattern_file", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.pattern_file == "file");
  }
}

TEST_CASE("OptParse complement", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-c", "both"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.complement == OptParse::OptComplement::Both);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--complement", "both"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.complement == OptParse::OptComplement::Both);
  }
}

TEST_CASE("OptParse direction", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-d", "reverse"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.direction == OptParse::OptDirection::Reverse);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--direction", "reverse"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.direction == OptParse::OptDirection::Reverse);
  }
}

TEST_CASE("OptParse start", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-s", "123"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.start == 123);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--start", "123"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.start == 123);
  }
}

TEST_CASE("OptParse end", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-e", "123"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.end == 123);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--end", "123"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.end == 123);
  }
}

TEST_CASE("OptParse threads", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-t", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.threads == 12);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--threads", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.threads == 12);
  }
}

TEST_CASE("OptParse score_encoding", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-E", "Phred64"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred64);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--score_encoding", "Phred64"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred64);
  }
}

TEST_CASE("OptParse score_min", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-S", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.score_min == 12);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--score_min", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.score_min == 12);
  }
}

TEST_CASE("OptParse ambiguate", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 2;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-a"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.ambiguate);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--ambiguate"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.ambiguate);
  }
}

TEST_CASE("OptParse match_type", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-m", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.match_type == 12);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--match_type", "12"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.match_type == 12);
  }
}

TEST_CASE("OptParse match_file", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-M", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.match_file == "file");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--match_file", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.match_file == "file");
  }
}

TEST_CASE("OptParse output", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-o", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.output == "file");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--output", "file"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.output == "file");
  }
}

TEST_CASE("OptParse overlap", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 2;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-O"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.overlap);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--overlap"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.overlap);
  }
}

TEST_CASE("OptParse filter", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 3;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-f", "filter"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.filter == "filter");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--filter", "filter"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.filter == "filter");
  }
}

TEST_CASE("OptParse version", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 2;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-v"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.version);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--version"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.version);
  }
}

TEST_CASE("OptParse verbose", "[optparse]") {
  optind   = 1;  // reset getopt
  int argc = 2;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-V"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.verbose);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--verbose"};

    OptParse opt_parse(argc, (char**)argv);

    REQUIRE(opt_parse.options_.verbose);
  }
}

TEST_CASE("OptParse w/o pattern or pattern_file raises", "[optparse]") {
  int        argc    = 1;
  const char *argv[] = {"seqscan"};

  REQUIRE_THROWS_AS(OptParse opt_parse(argc, (char**)argv), OptParseException);
}

TEST_CASE("OptParse w pattern and pattern_file raises", "[optparse]") {
  int        argc    = 5;
  const char *argv[] = {"seqscan", "-p", "ATC", "-P", "file"};

  REQUIRE_THROWS_AS(OptParse opt_parse(argc, (char**)argv), OptParseException);
}

TEST_CASE("OptParse w grouped short options can be set OK") {
  int        argc    = 3;
  const char *argv[] = {"seqscan", "-vVp", "ATC"};

  OptParse opt_parse(argc, (char**)argv);

  REQUIRE(opt_parse.options_.version);
  REQUIRE(opt_parse.options_.verbose);
  REQUIRE(opt_parse.options_.pattern == "ATC");
}
