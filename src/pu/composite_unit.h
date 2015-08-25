#ifndef COMPOSITE_UNIT_H_
#define COMPOSITE_UNIT_H_

#include <vector>
#include "pattern_unit.h"

class CompositeUnit: public PatternUnit
{
public:
  CompositeUnit(const Modifiers &modifiers);

  void AddUnit(std::unique_ptr<PatternUnit> &unit);

  void Print();

  //TODO: Implement
  void Initialize(
      std::string::const_iterator pos,
      const std::string::const_iterator &max_pos
  ){}
  //TODO: Implement
  bool HasNextMatch(){ return false; }
  //TODO: Implement
  Match& NextMatch(){ Match m(0,0,0); return m;  };

private:
  std::vector< std::unique_ptr<PatternUnit> > punits;
};

#endif  // COMPOSITE_UNIT_H_
