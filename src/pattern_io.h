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

 #include <iostream>
 #include <string>
 #include <vector>

 /**
 * @brief Exception class for PatternIO class.
 *
 * @example
 *   std::string msg = "Exception message";
 *   throw PatternIOException(msg);
 */
class PatternIOException : public std::exception {
 public:
  PatternIOException(std::string &msg) :
    exceptionMsg(msg)
  {}

  PatternIOException(const PatternIOException &e) :
    exceptionMsg(e.exceptionMsg)
  {}

  virtual const char* what() const throw() { return exceptionMsg.c_str(); }

  const std::string exceptionMsg;
};

/**
* @brief Class for parsing patterns from a given ASCII text file with one pattern
* per line.
*
* @param path Path to pattern file.
*/
class PatternIO {
 public:
  PatternIO(const std::string &pat_file, std::vector<std::string> patterns);

  ~PatternIO();

 private:

  /*
   * Path to pattern file.
   */
  const std::string pat_file_;

  /*
   * Vector of strings with patterns.
   */
  std::vector<std::string> patterns_;

  /*
   * Parse pattern file.
   */
  void Parse();

  /*
   * Check if any patterns were parsed.
   */
  void CheckPatterns();
};
