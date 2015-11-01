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

#include "kmp_unit.h"

KMPUnit::KMPUnit(const Modifiers &modifiers, const std::string& pattern):
    BacktrackUnit(modifiers, pattern)
{
  BuildTransitions();
}


bool KMPUnit::FindMatch() {
  //Inspired by http://www.sanfoundry.com/cpp-program-implement-kruth-morris-patt-algorithm-kmp/

  last_found_matches_.clear();
  last_found_index_ = 0;

  const int m = pattern_.length();
  int k = 0; //Pattern position

  while (sequence_iterator_!=sequence_iterator_end_) {
    if (k == -1) {
      ++sequence_iterator_;
      k = 0;
    } else if (modifiers_.res_matcher_.Match(*sequence_iterator_,pattern_[k])) {
      ++sequence_iterator_;
      k++;
      if (k == m) { // There was a match
        Match match(sequence_iterator_ - m, m, 0);
        last_found_matches_.insert(match);
        sequence_iterator_ -= (m-1); //Ensures that overlapping matches are reported

        return true;
      }
    } else {
      k = transitions[k];
    }
  }
  return false;

}

void KMPUnit::BuildTransitions()
{
  //Inspired by http://www.sanfoundry.com/cpp-program-implement-kruth-morris-patt-algorithm-kmp/
  int m = pattern_.length();
  int k;

  transitions.resize(m);
  transitions[0] = -1;

  for (int i = 1; i < m; i++) {
    k = transitions[i - 1];
    while (k >= 0) {
      if (pattern_[k] == pattern_[i - 1]) break;
      else k = transitions[k];
    }
    transitions[i] = k + 1;
  }
}

