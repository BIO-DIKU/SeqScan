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

#ifndef SEQSCAN_MATRIX_IO_H_
#define SEQSCAN_MATRIX_IO_H_

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Exception class for MatrixIO class.
 *
 * @example
 *   std::string msg = "Exception message";
 *   throw MatrixIOException(msg);
 */
class MatrixIOException : public std::exception {
public:
 MatrixIOException(std::string &msg) :
   exceptionMsg(msg)
 {}

 MatrixIOException(const MatrixIOException &e) :
   exceptionMsg(e.exceptionMsg)
 {}

 virtual const char* what() const throw() { return exceptionMsg.c_str(); }

 const std::string exceptionMsg;
};

/**
 * @brief Class for parsing residue match matrices from a given ASCII text file.
 * A match matrix file may contain one or two matrices. For protein matching a
 * single match matrix must be present, and for nucleotide matching two matrices
 * must be present - one for forward matching and one for complement matching.
 *
 * The first row denotes sequence residues and the first column denotes pattern
 * residues. Below is an example of a match file with matrices for matching only
 * uppercase DNA/RNA and complement matching of the same (if the ~ operator is
 * used a complement matrix must also be defined). Matching residues are
 * indicated by + in the row and column intersection.
 *
 *  ACGTU
 * A+
 * C +
 * G  +
 * T   ++
 * U   ++
 *
 * ~ACGTU
 * A   ++
 * C  +
 * G +
 * T+
 * U+
 *
 * @param Path to matrix file.
 * @param Vector for holding matrix lines.
 */
class MatrixIO {
 public:
  MatrixIO(std::string              matrix_file,
           std::vector<std::string> &matrix,
           std::vector<std::string> &matrix_comp);

  ~MatrixIO();

 private:

  /*
   * Path to matrix file.
   */
  const std::string matrix_file_;

  /*
   * Vector of strings with matrix lines.
   */
  std::vector<std::string>& matrix_;

  /*
   * Vector of strings with complement matrix lines.
   */
  std::vector<std::string>& matrix_comp_;

  /*
   * Parse matrix file.
   */
  void Parse();

  /*
   * Check that matrices are not empty.
   */
  void CheckMatrices();
};

#endif  // SEQSCAN_MATRIX_IO_H_
