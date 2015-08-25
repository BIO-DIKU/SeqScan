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

  void Initialize(
      std::string::const_iterator pos,
      std::string::const_iterator max_pos
  );
  bool HasNextMatch();
  Match& NextMatch();

private:
  std::vector< std::unique_ptr<PatternUnit> > punits_;
};

#endif  // COMPOSITE_UNIT_H_
