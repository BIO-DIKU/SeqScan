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

#include "match.h"

Match::Match(const std::string::const_iterator &pos, const int &len, const int &edits):
    pos(pos), len(len), edits(edits)
{}

Match::Match(const std::vector< Match >& sub_matches):
    pos(sub_matches[0].pos),
    len(TotalLen(sub_matches)),
    edits(TotalEdits(sub_matches)),
    sub_matches_(sub_matches)
{}

int Match::TotalLen(const std::vector< Match >& sub_matches) {
  int length = 0;
  for (auto &match : sub_matches) {
    length += match.len;
  }
  return length;
}

int Match::TotalEdits(const std::vector< Match >& sub_matches) {
  int edits = 0;

  for (auto &match : sub_matches) {
    edits += match.edits;
  }

  return edits;
}

std::ostream& Match::Print(std::ostream& os, const std::string::const_iterator& seq_start) const {
  if (sub_matches_.empty()) {
    os << (pos - seq_start) << "," << len << "," << edits << ",";

    // Write from pos and len characters forward.
    std::string::const_iterator it = pos;
    for (auto l = 0; l < len; l++) {
      os << *it;
      ++it;
    }

  } else {
    for (size_t c = 0; c < sub_matches_.size(); c++) {
      if (c > 0) os << ";";

      sub_matches_[c].Print(os, seq_start);
    }
  }

  return os;
}
