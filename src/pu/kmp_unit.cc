//
// Created by Rasmus Fonseca on 30/10/15.
//

#include "kmp_unit.h"

KMPUnit::KMPUnit(const Modifiers &modifiers, const std::string& pattern):
    BacktrackUnit(modifiers, pattern)
{
  BuildTransitions();
}


bool KMPUnit::FindMatch() {

  last_found_matches_.clear();
  last_found_index_ = 0;
  int m = pattern_.length();

  int i = 0;
  int k = 0;
  //while (i < n)
  while (sequence_iterator_!=sequence_iterator_end_)
  {
    if (k == -1) {
      //i++;
      ++sequence_iterator_;
      k = 0;
    } else if (*sequence_iterator_ == pattern_[k]) {
      //i++;
      ++sequence_iterator_;
      k++;
      if (k == m) { // There was a match
        Match match(sequence_iterator_ - m, m, 0);
        last_found_matches_.insert(match);

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
  //From http://www.sanfoundry.com/cpp-program-implement-kruth-morris-patt-algorithm-kmp/
  //void preKMP(string pattern, int f[])
  int m = pattern_.length();
  transitions.resize(m);
  int k;
  transitions[0] = -1;
  for (int i = 1; i < m; i++)
  {
    k = transitions[i - 1];
    while (k >= 0) {
      if (pattern_[k] == pattern_[i - 1])
        break;
      else
        k = transitions[k];
    }
    transitions[i] = k + 1;
  }
}

