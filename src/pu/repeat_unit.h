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

#ifndef SEQSCAN_REPEAT_UNIT_H
#define SEQSCAN_REPEAT_UNIT_H

#import "pattern_unit.h"

class RepeatUnit: public PatternUnit {

public:
  RepeatUnit(const Modifiers &modifiers, const int &min_repeats, const int &max_repeats) :
      PatternUnit(modifiers),
      min_repeats_(min_repeats),
      max_repeats_(max_repeats)
  { }

private:
  int min_repeats_;
  int max_repeats_;
};


#endif //SEQSCAN_REPEAT_UNIT_H
