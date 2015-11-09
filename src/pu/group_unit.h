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

#ifndef SEQSCAN_GROUP_UNIT_H_
#define SEQSCAN_GROUP_UNIT_H_

#include "pattern_unit.h"

/**
 * Pattern unit for matching a group of specified residues e.g. [ATC] with the
 * option of also negating the matching e.g. [^ATC].
 */
class GroupUnit : public PatternUnit {
 public:
  GroupUnit(const Modifiers &modifiers, const std::string &pattern, const bool &negator);

 protected:
  const std::string pattern_;
  const bool        negator_;
};

#endif  // SEQSCAN_GROUP_UNIT_H_
