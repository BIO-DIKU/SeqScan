#ifndef BACKTRACK_SEQUENCE_UNIT_H
#define BACKTRACK_SEQUENCE_UNIT_H


#include "pattern_unit.h"

class BacktrackSequenceUnit: public PatternUnit{

public:
  BacktrackSequenceUnit(const Modifiers &modifiers, const std::string& pattern);

  //TODO: Implement
  void Initialize(
      std::string::const_iterator pos,
      const std::string::const_iterator& max_pos
  ){}
  //TODO: Implement
  bool HasNextMatch(){ return false; }
  //TODO: Implement
  Match& NextMatch(){ Match m(0,0,0); return m;  };

private:
  const std::string pattern_;
};


#endif // BACKTRACK_SEQUENCE_UNIT_H
