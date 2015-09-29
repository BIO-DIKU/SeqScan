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

#ifndef SEQSCAN_IO_H
#define SEQSCAN_IO_H

#include <string>
#include <utility>
#include <vector>

class IO {
public:
  /**
   * Read a FASTA file. The result is returned as a vector of pairs where the first pair-member
   * is the header entry and the second is the sequence, stripped of whitespaces and all
   * upper-cased.
   */
  static std::vector< std::pair<std::string,std::string>> read_fasta(const std::string& fname);
};

#endif  // SEQSCAN_IO_H
