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

#include "optparse.h"

using namespace std;

OptParse::OptParse(int argc, char *argv[]) {


}

bool OptParse::Parse() {
  int option_index                  = 0;
  string opt_string                 = OptParse.
  struct OptTemplate opt_template[];
  struct Options     options        = SetOptDefaults();

  while ((int opt = getopt_long(argc, argv, opt_string, opt_template,
                                &option_index)) != -1) {
    switch (opt) {
      case 'h':   // help
        options.help = atoi(optarg) ? true : false;
        break;
      case 'p':   // pattern
        options.output = optarg;
        break;
      case 'P':   // pattern_file
        options.output = optarg;
        break;
      case 'c':   // complement
        options.complement = ParseComplement(optarg);
        break;
      case 'd':   // direction
        options.direction = ParseDirection(optarg);
        break;
      case 's':   // start
        options.start = atoi(optarg);
        break;
      case 'e':   // end
        options.end = atoi(optarg);
        break;
      case 't':   // threads
        options.score_min = atoi(optarg);
        break;
      case 'E':   // score_encoding
        optinos.score_encoding = ParseScoreEnconding(optarg);
        break;
      case 'S':   // score_min
        options.score_min = atoi(optarg);
        break;
      case 'a':   // ambiguate
        options.help = atoi(optarg) ? true : false;
        break;
      case 'm':   // match_type
        options.end = atoi(optarg);
        break;
      case 'M':   // match_file
        options.output = optarg;
        break;
      case 'o':   // output
        options.output = optarg;
        break;
      case 'O':   // overlap
        options.help = atoi(optarg) ? true : false;
        break;
      case 'f':   // filter
        options.filter = optarg;
        break;
      case 'v':   // version
        options.help = atoi(optarg) ? true : false;
        break;
      case 'V':   // verbose
        options.help = atoi(optarg) ? true : false;
        break;
      default:
        cerr << "unexpected argument: ->" << optarg << "<-" << endl;
        return false;
    }
  }

  // processing non-option arguments i.e. sequence files.
  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);

  return true;
}

inline const OptCompare ParseComplement(optarg) { // FIXME I have no idea what the type of optarg is?
  if (optarg == "forward") {
    return Forward;
  } else if (optarg == "reverse") {
    return Reverse;
  } else if (optarg == "both") {
    return Both;
  } else {
    // TODO(Martin): Collapse universe.
  }
}

inline const OptDirection ParseDirection(optarg) { // FIXME I have no idea what the type of optarg is?
  if (optarg == "forward") {
    return Forward;
  } else if (optarg == "reverse") {
    return Reverse;
  } else {
    // TODO(Martin): Collapse universe.
  }
}

inline const OptScoreEncoding ParseScoreEncoding(optarg) { // FIXME I have no idea what the type of optarg is?
  if (optarg == "Phred33") {
    return Phread33;
  } else if (optarg == "Phread64") {
    return Phread64;
  } else {
    // TODO(Martin): Collapse universe.
  }
}

// FIXME(Martin) get rid of magic numbers.
void OptParse::SetOptDefaults() {
  options.help          = false;
  options.complement    = Forward;
  options.direction     = Forward;
  options.threads       = 1;
  option.score_encoding = Phred33;
  optinos.score_min)    = 25;
  options.ambiguate     = false;
  options.match_type    = 1;
  options.overlap       = false;
  options.version       = false;
  options.verbose       = false;
}

void OptParse::PrintOptions() {
  cerr << "Options: " << endl;
  cerr << "  help: "           << boolalpha << options.help << endl;
  cerr << "  pattern: "        << options.pattern << endl;
  cerr << "  pattern_file: "   << options.pattern_file << endl;
  cerr << "  complement: "     << ComplementToString(options.complement) << endl;
  cerr << "  direction: "      << DirectionToString(options.direction) << endl;
  cerr << "  start: "          << to_string(options.start) << endl;
  cerr << "  end: "            << to_string(options.end) << endl;
  cerr << "  threads: "        << to_string(options.threads) << endl;
  cerr << "  score_encoding: " << ScoreEncodingToString(option.score_encoding) << endl;
  cerr << "  score_min: "      << to_string(optinos.score_min) << endl;
  cerr << "  ambiguate: "      << boolalpha << options.ambiguate << endl;
  cerr << "  match_type: "     << to_string(options.match_type) << endl;
  cerr << "  match_file: "     << options.match_file << endl;
  cerr << "  output: "         << options.output << endl;
  cerr << "  overlap: "        << boolalpha << options.overlap << endl;
  cerr << "  filter: "         << options.filter << endl;
  cerr << "  version: "        << boolalpha << options.version << endl;
  cerr << "  verbose: "        << boolalpha << options.verbose << endl;
}

inline const char* ComplementToString(OptComplement opt) {
  switch (opt) {
    case Forward: return "forward";
    case Reverse: return "reverse";
    case Both:    return "both";
    default:      return "Unknown complement option";
  }
}

inline const char* DirectionToString(OptDirection opt) {
  switch (opt) {
    case Forward: return "forward";
    case Reverse: return "reverse";
    default:      return "Unknown direction option";
  }
}

inline const char* ScoreEncodingToString(OptScoreEncoding opt) {
  switch (opt) {
    case Phred33: return "Phred33";
    case Phred64: return "Phred64";
    default:      return "Unknown score_encoding option";
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
