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

#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

#include "optparse.h"

using namespace std;

OptParse::OptParse(int argc, char *argv[]) :
  argc_(argc),
  argv_(argv),
  files_(),
  options_() {
  SetOptDefaults();
  Parse();
}

void OptParse::SetOptDefaults() {
  options_.help           = false;
  options_.complement     = OptComplement::Forward;
  options_.direction      = OptDirection::Forward;
  options_.threads        = kDefaultThreads;
  options_.score_encoding = OptScoreEncoding::Phred33;
  options_.score_min      = kDefaultScoreMin;
  options_.ambiguate      = false;
  options_.match_type     = kDefaultMatchType;
  options_.overlap        = false;
  options_.version        = false;
  options_.verbose        = false;
}

bool OptParse::Parse() {
  int opt_index = 0;
  int opt       = 0;

  while ((opt = getopt_long(argc_, argv_, opt_string_.c_str(), opt_templates_, &opt_index)) != -1) {
    switch (opt) {
      case 'h':
        options_.help = atoi(optarg) ? true : false;
        break;
      case 'p':
        options_.pattern = string(optarg);
        break;
      case 'P':
        options_.pattern_file = string(optarg);
        break;
      case 'c':
        options_.complement = ParseComplement(string(optarg));
        break;
      case 'd':
        options_.direction = ParseDirection(string(optarg));
        break;
      case 's':
        options_.start = atoi(optarg);
        break;
      case 'e':
        options_.end = atoi(optarg);
        break;
      case 't':
        options_.score_min = atoi(optarg);
        break;
      case 'E':
        options_.score_encoding = ParseScoreEncoding(string(optarg));
        break;
      case 'S':
        options_.score_min = atoi(optarg);
        break;
      case 'a':
        options_.ambiguate = atoi(optarg) ? true : false;
        break;
      case 'm':
        options_.match_type = atoi(optarg);
        break;
      case 'M':
        options_.match_file = string(optarg);
        break;
      case 'o':
        options_.output = string(optarg);
        break;
      case 'O':
        options_.help = atoi(optarg) ? true : false;
        break;
      case 'f':
        options_.filter = string(optarg);
        break;
      case 'v':
        options_.help = atoi(optarg) ? true : false;
        break;
      case 'V':
        options_.help = atoi(optarg) ? true : false;
        break;
      default:
        cerr << "Unexpected argument: ->" << optarg << "<-" << endl;
        return false;
    }
  }

  for (int index = optind; index < argc_; index++) {
    files_.push_back(argv_[index]);
  }

  return true;
}

void OptParse::PrintOptions() {
  cerr << "Options: " << endl;
  cerr << "  help:           " << boolalpha << options_.help << endl;
  cerr << "  pattern:        " << options_.pattern << endl;
  cerr << "  pattern_file:   " << options_.pattern_file << endl;
  cerr << "  complement:     " << ComplementToString(options_.complement) << endl;
  cerr << "  direction:      " << DirectionToString(options_.direction) << endl;
  cerr << "  start:          " << to_string(options_.start) << endl;
  cerr << "  end:            " << to_string(options_.end) << endl;
  cerr << "  threads:        " << to_string(options_.threads) << endl;
  cerr << "  score_encoding: " << ScoreEncodingToString(options_.score_encoding) << endl;
  cerr << "  score_min:      " << to_string(options_.score_min) << endl;
  cerr << "  ambiguate:      " << boolalpha << options_.ambiguate << endl;
  cerr << "  match_type:     " << to_string(options_.match_type) << endl;
  cerr << "  match_file:     " << options_.match_file << endl;
  cerr << "  output:         " << options_.output << endl;
  cerr << "  overlap:        " << boolalpha << options_.overlap << endl;
  cerr << "  filter:         " << options_.filter << endl;
  cerr << "  version:        " << boolalpha << options_.version << endl;
  cerr << "  verbose:        " << boolalpha << options_.verbose << endl;
}

const char* OptParse::ComplementToString(OptComplement opt) {
  switch (opt) {
    case OptComplement::Forward: return "forward";
    case OptComplement::Reverse: return "reverse";
    case OptComplement::Both:    return "both";
    default:                     return "Unknown complement option";
  }
}

const char* OptParse::DirectionToString(OptDirection opt) {
  switch (opt) {
    case OptDirection::Forward: return "forward";
    case OptDirection::Reverse: return "reverse";
    default:                    return "Unknown direction option";
  }
}

const char* OptParse::ScoreEncodingToString(OptScoreEncoding opt) {
  switch (opt) {
    case OptScoreEncoding::Phred33: return "Phred33";
    case OptScoreEncoding::Phred64: return "Phred64";
    default:                        return "Unknown score_encoding option";
  }
}

const OptParse::OptComplement OptParse::ParseComplement(string optarg) {
  if (optarg == "forward") {
    return OptComplement::Forward;
  } else if (optarg == "reverse") {
    return OptComplement::Reverse;
  } else if (optarg == "both") {
    return OptComplement::Both;
  } else {
    string msg = "Bad argument for complement option: " + optarg;
    throw OptParseException(msg);
  }
}

const OptParse::OptDirection OptParse::ParseDirection(string optarg) {
  if (optarg == "forward") {
    return OptDirection::Forward;
  } else if (optarg == "reverse") {
    return OptDirection::Reverse;
  } else {
    string msg = "Bad argument for direction option: " + optarg;
    throw OptParseException(msg);
  }
}

const OptParse::OptScoreEncoding OptParse::ParseScoreEncoding(string optarg) {
  if (optarg == "Phred33") {
    return OptScoreEncoding::Phred33;
  } else if (optarg == "Phred64") {
    return OptScoreEncoding::Phred64;
  } else {
    string msg = "Bad argument for score_encoding option: " + optarg;
    throw OptParseException(msg);
  }
}

void OptParse::PrintUsage() {
  cerr << R"USAGE(
Usage: seqscan [options] <file(s)>

   [options]:
   -h --help                               Print this help menu.
   -p --pattern <pattern>                  Pattern to use, see the pattern
                                           section in the documentation.
   -P --pattern_file <string>              File with list of patterns, one
                                           per line.
   -c --complement <forward|reverse|both>  Scan the forward, reverse or
                                           both strands
                                           (default=forward).
   -d --direction <forward|reverse>        Scan direction
                                           (default=forward).
   -s --start <int>                        Start scanning position
                                           (default=1).
   -e --end <int>                          End scanning position.
   -t --threads <int>                      Threads to use (default=1).
   -E --score_encoding <Phred33|Phred64>   Specify FASTQ score encoding
                                           (default=Phred33).
   -S --score_min <int>                    Minimum Phred score in matches.
   -a --ambiguate                          Ambiguate residues with score
                                           below the minimum Phred score.
   -m --match_type <int>                   Match type used (default=4):

      Features:
         N: Nucleotide.
         P: Protein.
         A: Ambiguity codes.
         I: Case insensitive.

      Match type   Sequence   Pattern
      ----------   --------   -------
      1            N          N
      2            NI         NI
      3            NIA        NI
      4            NI         NIA
      5            NIA        NIA
      6            P          P
      7            PI         PI

   -M --match_file <string>                File with custom match type
                                           matrices.
   -o --output <string>                    Output file.
   -O --overlap                            Output overlapping matches.
   -f --filter <filter>                    Filter matches, see the filter
                                           section in the documentation.
   -v --version                            Output program version.
   -V --verbose                            Enable verbose messages.

Documentation: https://github.com/BIO-DIKU/SeqScan
)USAGE" << endl;
}
