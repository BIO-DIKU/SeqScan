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

#include "modifiers.h"
#include "res_matcher.h"

Modifiers::Modifiers(
    const int max_edits,
    const int mismatches,
    const int insertions,
    const int deletions,
    const int indels,
    const bool reverse,
    const ResMatcher res_matcher,
    const std::string label
):
    max_edits_(max_edits),
    mismatches_(mismatches),
    insertions_(insertions),
    deletions_(deletions),
    indels_(indels),
    reverse_(reverse),
    res_matcher_(res_matcher),
    label_(label)
{
}

std::ostream& Modifiers::PrintPUPrefix(std::ostream &os) const {
//  if (!label_.empty())
//    os << label_ << "=";
//
//  if (reverse_ && complement_) os << "~";
//  else if (reverse_) os << "<";
//  else if (complement_) os << "<~";

  return os;
}

std::ostream& Modifiers::PrintPUSuffix(std::ostream &os) const {
  if (max_edits_) os << "/" << max_edits_;

  if (indels_)
    os << "/" << mismatches_ << "," << indels_;
  else if (mismatches_ || insertions_ || deletions_)
    os << "/" << mismatches_ << "," << insertions_ << "," << deletions_;

  return os;
}

Modifiers Modifiers::CreateStdModifiers() {
  ResMatcher rm(6);
  Modifiers ret(0, 0, 0, 0, 0, false, rm , "");
  return std::move(ret);
}

Modifiers Modifiers::CreateMIDModifiers(
    const int mismatches,
    const int insertions,
    const int deletions)
{
  ResMatcher rm(6);
  Modifiers ret(0, mismatches, insertions, deletions, 0, false, rm, "");
  return std::move(ret);
}
