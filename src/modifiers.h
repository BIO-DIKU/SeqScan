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

#ifndef SEQSCAN_MODIFIERS_H_
#define SEQSCAN_MODIFIERS_H_

#include <memory>
#include <string>
#include <iostream>

#include "res_matcher.h"

class Modifiers {
 public:
  Modifiers(
      const int max_edits,
      const int mismatches,
      const int insertions,
      const int deletions,
      const int indels,
      const bool reverse,
      const ResMatcher res_matcher,
      const std::string label
  );

  const int max_edits_;
  const int mismatches_;
  const int insertions_;
  const int deletions_;
  const int indels_;
  const bool reverse_;
  const ResMatcher res_matcher_;
  const std::string label_;

  /** Outputs the modifiers that goes before the pattern-unit */
  std::ostream& PrintPUPrefix(std::ostream &os) const;

  /** Outputs the modifiers that goes after the pattern-unit */
  std::ostream& PrintPUSuffix(std::ostream &os) const;

  static Modifiers CreateStdModifiers(const ResMatcher res_matcher);

  static Modifiers CreateMIDModifiers(
      const ResMatcher res_matcher,
      const int        mismatches,
      const int        insertions,
      const int        deletions
  );
};

#endif  // SEQSCAN_MODIFIERS_H_
