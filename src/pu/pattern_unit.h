#ifndef PU_PATTERNUNIT_H_
#define PU_PATTERNUNIT_H_

#include <string>

#include "../match.h"
#include "../Modifiers.h"

/*
 * An abstract pattern unit that holds modifiers and specifies an iterator pattern over matches.
 * The return value of HasNextMatch and NextMatch are undefined before Initialize has been called. NextMatch
 * is only guaranteed to be specified if HasNextMatch returns true. The intended use is roughly as follows:
 *    unique_ptr<PatternUnit> pu = ...
 *    string sequence = ...
 *    pu->Initialize( sequence.cbegin(), sequence.cend() );
 *    while( pu->HasNextMatch() ){
 *      Match& m = pu->NextMatch();
 *      // Do something with m
 *    }
 */
class PatternUnit
{
public:
  /*
   * Construct a pattern unit with the specified modifiers
   */
  PatternUnit(const Modifiers& modifiers);

  /*
   * Initialize the pattern unit so the match iteration will start at pos
   */
  virtual void Initialize(
      std::string::const_iterator pos,
      const std::string::const_iterator& max_pos
  ) = 0;

  /*
   * Returns true iff there its possible to locate a match following the previous found. If NextMatch has not been
   * called it will be the match starting at the earliest position with the lowest possible length.
   * The return value of this function is only specified if Initialize has previously been called.
   */
  virtual bool HasNextMatch() = 0;

  /*
   * Returns the next match.
   * The return value of this function is only specified if HasNextMatch has previously been called and returned true.
   * The referenced match will only change on the next call to HasNextMatch.
   */
  virtual Match& NextMatch() = 0;

protected:
  const Modifiers modifiers_;

};

#endif  // PU_PATTERNUNIT_H_

