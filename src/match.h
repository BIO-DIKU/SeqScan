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

#ifndef MATCH_H_
#define MATCH_H_

#include <string>
#include <iostream>
#include <iostream>

class Match {
public:
  Match(const std::string::const_iterator &pos, const int &len, const int &edits):
      pos(pos), len(len), edits(edits)
  {}

  //const std::string::const_iterator pos;
  const std::string::const_iterator pos;
  const int len;
  const int edits;

  bool operator<(const Match& rhs) const{
    return pos==rhs.pos?len<rhs.len:pos<rhs.pos;
  }

};

#endif  // MATCH_H_
