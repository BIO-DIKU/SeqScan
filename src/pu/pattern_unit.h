#ifndef PU_PATTERNUNIT_H_
#define PU_PATTERNUNIT_H_

#include <string>

#include "../match.h"
#include "../Modifiers.h"

/*
 * An abstract pattern unit that holds modifiers and specifies an iterator pattern over matches.
 * The return value of HasNextMatch, NextMatch and PrevMatch are undefined before Initialize has been called. NextMatch
 * is only guaranteed to be specified if HasNextMatch returns true. PrevMatch is only specified if NextMatch has been
 * called. The intended use is as follows:
 *    unique_ptr<PatternUnit> pu = ...
 *    string sequence = ...
 *    pu->Initialize( sequence.cbegin() );
 *    while( pu->HasNextMatch() ){
 *      Match& m = pu->NextMatch();
 *      // Do something with m
 *    }
 */
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

