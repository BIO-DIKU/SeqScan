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

static int OptParse(int argc, char *argv[], struct options long_options) {
  int option_index = 0;

  while ((int opt = getopt_long(argc, argv, "hp:P:c:d:s:e:t:E:S:am:M:o:Of:vV",
                                long_options, &option_index)) != -1) {
    switch (opt) {
      case 'h':   // help
        MainControl::instance()->setIdentity(atof(optarg));
        break;
      case 'p':   // pattern
        break;
      case 'P':   // pattern_file
        break;
      case 'c':   // complement
        break;
      case 'd':   // direction
        break;
      case 's':   // start
        break;
      case 'e':   // end
        break;
      case 't':   // threads
        break;
      case 'E':   // score_encoding
        break;
      case 'S':   // score_min
        break;
      case 'a':   // ambiguate
        break;
      case 'm':   // match_type
        break;
      case 'M':   // match_file
        break;
      case 'o':   // output
        break;
      case 'O':   // overlap
        break;
      case 'f':   // filter
        break;
      case 'v':   // version
        break;
      case 'V':   // verbose
        break;
      default:
        std::cerr << "unexpected argument" << std::endl;
        return false;
    }
  }

  return true;
}

static void PrintUsage() {
  std::cerr << R"USAGE(
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
)USAGE" << std::endl;
}
