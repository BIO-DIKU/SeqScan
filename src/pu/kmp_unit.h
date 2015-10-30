//
// Created by Rasmus Fonseca on 30/10/15.
//

#ifndef SEQSCAN_KMP_UNIT_H
#define SEQSCAN_KMP_UNIT_H

#include <vector>

#include "backtrack_unit.h"

class KMPUnit : public BacktrackUnit{
 public:
  KMPUnit(const Modifiers &modifiers, const std::string& pattern);

  bool FindMatch();

 private:
  void BuildTransitions();
  std::vector<int> transitions;

};


#endif //SEQSCAN_KMP_UNIT_H
