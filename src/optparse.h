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

/*
 * Optios stucture for holding what-the-hell-is-it?
 * TODO(Martin) find the proper getopt web page and figure out what is going on.
 */
static struct options long_options[] = {
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
};

/*
 * Parse options from argv and save the result in long_options.
 * Returns true if parsing was OK else false.
 */
static bool OptParse(int argc, char *argv[], struct options long_options);

/*
 * Print usage to stderr.
 */
static void PrintUsage();

#endif  // SEQSCAN_OPTPARSE_H_
