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

#ifndef SEQSCAN_OPTPARSE_H_
#define SEQSCAN_OPTPARSE_H_

#include <string>
#include <vector>

/**
 * @brief Class for parsing command line arguments using Getopt-Long:
 *
 * http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
 *
 * OptParse holdes a struct with Options and a vector of non-option arguments
 * i.e. files.
 */
class OptParse {
 public:
  OptParse(int argc, char *argv[]);

  ~OptParse();

  /*
   * Struct for parsed command line options.
   */
  struct Options {
    bool             help;
    std::string      pattern;
    std::string      pattern_file;
    OptComplement    complement;
    OptDirection     direction;
    int              start;
    int              end;
    int              threads;
    OptScoreEncoding score_encoding;
    int              score_min;
    bool             ambiguate;
    int              match_type;
    std::string      match_file;
    std::string      output;
    bool             overlap;
    std::string      filter;
    bool             version;
    bool             verbose;
  } options;

  /*
   * Vector for holding non-option command line arguments i.e. sequence files.
   */
  std::vector<std::string> files;

  /*
   * Parse options from argv and save the result in Options struct.
   * Returns true if parsing was OK else false.
   */
  bool Parse();

  /*
   * Print options for debugging.
   */
  void PrintOptions();

  /*
   * Print usage to stderr.
   */
  void PrintUsage();

 private:

  int  argc;
  char *argv[];

 /*
  * Set options default to sane values
  */
 void SetOptDefaults();

  /*
   * Struct for holding option template.
   */
  struct OptTemplate {
    {"help",           no_argument,       0, 'h'},
    {"pattern",        required_argument, 0, 'p'},
    {"pattern_file",   required_argument, 0, 'P'},
    {"complement",     required_argument, 0, 'c'},
    {"direction",      required_argument, 0, 'd'},
    {"start",          required_argument, 0, 's'},
    {"end",            required_argument, 0, 'e'},
    {"threads",        required_argument, 0, 't'},
    {"score_encoding", required_argument, 0, 'E'},
    {"score_min",      required_argument, 0, 'S'},
    {"ambiguate",      no_argument,       0, 'a'},
    {"match_type",     required_argument, 0, 'm'},
    {"match_file",     required_argument, 0, 'M'},
    {"output",         required_argument, 0, 'o'},
    {"overlap",        no_argument,       0, 'O'},
    {"filter" ,        required_argument, 0, 'f'},
    {"version",        no_argument,       0, 'v'},
    {"verbose",        no_argument,       0, 'V'},
    {0,                 0,                0,  0 }
  } opt_template[];

  /*
   * String with one char options followed by : iif the option requies an
   * argument.
   */
  std::string opt_string = "hp:P:c:d:s:e:t:E:S:am:M:o:Of:vV";

  /*
   * Enum for direction option.
   */
  enum OptDirection {
    Forward,
    Reverse
  };

  /*
   * Enum for complement option.
   */
  enum OptComplement {
    Forward,
    Reverse,
    Both
  };

  /*
   * Enum for score encoding option.
   */
  enum OptScoreEncoding {
    Phred33,
    Phred64
  };

  /*
   * Inline function for parsing complement option into enum OptCompare.
   */
  inline const OptCompare ParseComplement(char *optarg) {
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

  /*
   * Inline function for parsing direction option into enum OptDirection.
   */
  inline const OptDirection ParseDirection(char *optarg) {
    if (optarg == "forward") {
      return Forward;
    } else if (optarg == "reverse") {
      return Reverse;
    } else {
      // TODO(Martin): Collapse universe.
    }
  }

  /*
   * Inline function for parsing score_encoding option into enum
   * OptScoreEncoding.
   */
  inline const OptScoreEncoding ParseScoreEncoding(char* optarg) {
    if (optarg == "Phred33") {
      return Phred33;
    } else if (optarg == "Phred64") {
      return Phred64;
    } else {
      // TODO(Martin): Collapse universe.
    }
  }
};

#endif  // SEQSCAN_OPTPARSE_H_
