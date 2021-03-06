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

#include <iostream>
#include <fstream>
#include "catch.h"
#include "opt_parse.h"

using namespace std;

TEST_CASE("OptParse w. bad option raises", "[opt_parse]") {
  int        argc    = 4;
  const char *argv[] = {"seqscan", "-p", "ATC", "-Z"};

  REQUIRE_THROWS_AS(OptParse opt_parse(argc, (char**)argv, true), OptParseException);
}

TEST_CASE("OptParse w. missing option argument raises", "[opt_parse]") {
  int        argc    = 4;
  const char *argv[] = {"seqscan", "-p", "ATC", "-X"};

  try {
    OptParse opt_parse(argc, (char**)argv, true);
    FAIL("opt_parse() did not throw expected exception");
  }
  catch (OptParseException& e) {
    REQUIRE(e.exceptionMsg == "option-parser: Unexpected argument: '?'");
  }
}

TEST_CASE("OptParse have correct default option values", "[opt_parse]") {
  int   argc         = 4;
  const char* argv[] = {"seqscan", "-p", "ATC", "file1"};

  OptParse opt_parse(argc, (char **)argv);

  REQUIRE(opt_parse.options_.help           == false);
  REQUIRE(opt_parse.options_.complement     == OptParse::OptComplement::Forward);
  REQUIRE(opt_parse.options_.direction      == OptParse::OptDirection::Forward);
  REQUIRE(opt_parse.options_.start          == kDefaultStart);
  REQUIRE(opt_parse.options_.end            == kDefaultEnd);
  REQUIRE(opt_parse.options_.threads        == kDefaultThreads);
  REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred33);
  REQUIRE(opt_parse.options_.score_min      == kDefaultScoreMin);
  REQUIRE(opt_parse.options_.ambiguate      == false);
  REQUIRE(opt_parse.options_.match_type     == kDefaultMatchType);
  REQUIRE(opt_parse.options_.overlap        == false);
  REQUIRE(opt_parse.options_.version        == false);
  REQUIRE(opt_parse.options_.verbose        == false);
}

TEST_CASE("OptParse help", "[opt_parse]") {
  int argc = 4;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-h"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.help);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--help"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.help);
  }
}

TEST_CASE("OptParse pattern", "[opt_parse]") {
  int argc = 4;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.pattern == "ATC");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--pattern", "ATC", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.pattern == "ATC");
  }
}

TEST_CASE("OptParse pattern_file", "[opt_parse]") {
  string file = "pfile";
  ofstream output;
  output.open(file);
  output << "p1=ATC" << endl;
  output << "" << endl;
  output << "ATG ... TGA" << endl;
  output.close();

  int argc = 4;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-P", "pfile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.pattern_file == "pfile");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "--pattern_file", "pfile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.pattern_file == "pfile");
  }

  remove(file.c_str());
}

TEST_CASE("OptParse complement", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-c", "both", "fil1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.complement == OptParse::OptComplement::Both);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--complement", "both", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.complement == OptParse::OptComplement::Both);
  }

  SECTION("bad value raises") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--complement", "foo", "file1"};

    REQUIRE_THROWS_AS(OptParse opt_parse(argc, (char**)argv, true), OptParseException);
  }
}

TEST_CASE("OptParse direction", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-d", "reverse", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.direction == OptParse::OptDirection::Reverse);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--direction", "reverse", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.direction == OptParse::OptDirection::Reverse);
  }

  SECTION("bad value raises") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--direction", "foo", "file1"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: Bad argument for direction option: foo");
    }
  }
}

TEST_CASE("OptParse start", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-s", "123", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.start == 123);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--start", "123", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.start == 123);
  }
}

TEST_CASE("OptParse end", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-e", "123", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.end == 123);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--end", "123", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.end == 123);
  }
}

TEST_CASE("OptParse threads", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-t", "12", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.threads == 12);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--threads", "12", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.threads == 12);
  }
}

TEST_CASE("OptParse score_encoding", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-E", "Phred64", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred64);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--score_encoding", "Phred64", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.score_encoding == OptParse::OptScoreEncoding::Phred64);
  }

  SECTION("bad value raises") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--score_encoding", "foo", "file1"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: Bad argument for score_encoding option: foo");
    }
  }
}

TEST_CASE("OptParse score_min", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-S", "12", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.score_min == 12);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--score_min", "12", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.score_min == 12);
  }
}

TEST_CASE("OptParse ambiguate", "[opt_parse]") {
  int argc = 5;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-a", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.ambiguate);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--ambiguate", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.ambiguate);
  }
}

TEST_CASE("OptParse match_type", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-m", "10", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.match_type == 10);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--match_type", "10", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.match_type == 10);
  }
}

TEST_CASE("OptParse match_file", "[opt_parse]") {
  string file = "mfile";
  ofstream output;
  output.open(file);
  output << " AT" << endl;
  output << "A+ " << endl;
  output << "T +" << endl;
  output << "   " << endl;
  output << "~AT" << endl;
  output << "A +" << endl;
  output << "T+ " << endl;
  output.close();

  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-M", "mfile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.match_file == "mfile");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--match_file", "mfile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.match_file == "mfile");
  }

  remove(file.c_str());
}

TEST_CASE("OptParse output", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-o", "ofile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.output == "ofile");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--output", "ofile", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.output == "ofile");
  }
}

TEST_CASE("OptParse overlap", "[opt_parse]") {
  int argc = 5;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-O", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.overlap);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--overlap", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.overlap);
  }
}

TEST_CASE("OptParse filter", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-f", "filter", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.filter == "filter");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--filter", "filter", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.filter == "filter");
  }
}

TEST_CASE("OptParse version", "[opt_parse]") {
  int argc = 4;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-v"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.version);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--version"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.version);
  }
}

TEST_CASE("OptParse verbose", "[opt_parse]") {
  int argc = 5;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-V", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.verbose);
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--verbose", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.verbose);
  }
}

TEST_CASE("OptParse magic", "[opt_parse]") {
  int argc = 6;

  SECTION("short option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "-X", "foobar", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.magic == "foobar");
  }

  SECTION("long option can be set OK") {
    const char* argv[] = {"seqscan", "-p", "ATC", "--magic", "foobar", "file1"};

    OptParse opt_parse(argc, (char**)argv, true);

    REQUIRE(opt_parse.options_.magic == "foobar");
  }
}

TEST_CASE("OptParse w/o pattern or pattern_file raises", "[opt_parse]") {
  int        argc    = 2;
  const char *argv[] = {"seqscan", "file1"};

  try {
    OptParse opt_parse(argc, (char**)argv, true);
    FAIL("opt_parse() did not throw expected exception");
  }

  catch (OptParseException& e) {
    REQUIRE(e.exceptionMsg == "option-parser: Missing --pattern or --pattern_file");
  }
}

TEST_CASE("OptParse w pattern and pattern_file raises", "[opt_parse]") {
  int        argc    = 6;
  const char *argv[] = {"seqscan", "-p", "ATC", "-P", "file", "file1"};

  try {
    OptParse opt_parse(argc, (char**)argv, true);
    FAIL("opt_parse() did not throw expected exception");
  }

  catch (OptParseException& e) {
    REQUIRE(e.exceptionMsg == "option-parser: Both --pattern and --pattern_file given");
  }
}

TEST_CASE("OptParse w grouped short options can be set OK", "[opt_parse]") {
  int         argc   = 4;
  const char *argv[] = {"seqscan", "-Vp", "ATC", "file1"};

  OptParse opt_parse(argc, (char **) argv, true);

  REQUIRE(opt_parse.options_.verbose);
  REQUIRE(opt_parse.options_.pattern == "ATC");
}

TEST_CASE("OptParse w non-optional arguments", "[opt_parse]") {
  int        argc    = 5;
  const char *argv[] = {"seqscan", "-p", "ATC", "file1", "file2"};

  OptParse opt_parse(argc, (char**)argv, true);

  REQUIRE(opt_parse.files_.front() == "file1");
  REQUIRE(opt_parse.files_.back()  == "file2");
}

TEST_CASE("OptParse w/o non-optional arguments", "[opt_parse]") {
  SECTION("dont raise if -h given") {
    int        argc    = 2;
    const char *argv[] = {"seqscan", "-h"};

    REQUIRE_NOTHROW(OptParse opt_parse(argc, (char**)argv, true));
  }

  SECTION("raise if no -h given") {
    int        argc    = 3;
    const char *argv[] = {"seqscan", "-p", "ATC"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: No sequence file(s) given");
    }
  }
}

TEST_CASE("OptParse w. start and end", "[opt_parse]") {
  int argc = 8;

  SECTION("w. start < end don't raise") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-s", "1", "-e", "2", "file"};
    REQUIRE_NOTHROW(OptParse opt_parse(argc, (char**)argv, true));
  }

  SECTION("w. start == end don't raise") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-s", "1", "-e", "1", "file"};
    REQUIRE_NOTHROW(OptParse opt_parse(argc, (char**)argv, true));
  }

  SECTION("w. start > end raise") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-s", "2", "-e", "1", "file"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: start > end (2 > 1)");
    }
  }
}

TEST_CASE("OptParse w. complement and matrix w/o complement", "[opt_parse]") {
  int argc = 8;

  SECTION("complement forward") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "forward", "-m", "10", "file"};
    REQUIRE_NOTHROW(OptParse opt_parse(argc, (char**)argv, true));
  }

  SECTION("complement reverse") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "reverse", "-m", "10", "file"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: No complement match matrix");
    }
  }

  SECTION("complement both") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "both", "-m", "10", "file"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: No complement match matrix");
    }
  }
}

TEST_CASE("OptParse w. complement and matrix file w/o complement", "[opt_parse]") {
  string file = "mfile";
  ofstream output;
  output.open(file);
  output << " AT" << endl;
  output << "A+ " << endl;
  output << "T +" << endl;
  output.close();

  int argc = 8;

  SECTION("complement forward") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "forward", "-M", "mfile", "file"};
    REQUIRE_NOTHROW(OptParse opt_parse(argc, (char**)argv, true));
  }

  SECTION("complement reverse") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "reverse", "-M", "mfile", "file"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: No complement match matrix");
    }
  }

  SECTION("complement both") {
    const char *argv[] = {"seqscan", "-p", "ATC", "-c", "both", "-M", "mfile", "file"};

    try {
      OptParse opt_parse(argc, (char**)argv, true);
      FAIL("opt_parse() did not throw expected exception");
    }

    catch (OptParseException& e) {
      REQUIRE(e.exceptionMsg == "option-parser: No complement match matrix");
    }

    remove(file.c_str());
  }
}
