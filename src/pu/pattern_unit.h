#ifndef PU_PATTERNUNIT_H_
#define PU_PATTERNUNIT_H_

#include <string>

#include "../match.h"
#include "../Modifiers.h"

class PatternUnit
{
public:
  PatternUnit(const Modifiers& modifiers);

  virtual void Initialize(std::string::const_iterator& pos) = 0;

  virtual bool HasNextMatch() = 0;
  virtual Match& NextMatch() = 0;
  virtual Match& PrevMatch() = 0;

protected:
  const Modifiers modifiers_;

};

#endif  // PU_PATTERNUNIT_H_

