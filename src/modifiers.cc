//
// Created by Rasmus Fonseca on 25/08/15.
//

#include "modifiers.h"


Modifiers::Modifiers(
    const int max_edits,
    const int mismatches,
    const int insertions,
    const int deletions,
    const int min_repeats,
    const int max_repeats,
    const bool reverse,
    const bool complement,
    const bool greedy
):
    max_edits_(max_edits),
    mismatches_(mismatches),
    insertions_(insertions),
    deletions_(deletions),
    min_repeats_(min_repeats),
    max_repeats_(max_repeats),
    reverse_(reverse),
    complement_(complement),
    greedy_(greedy)
{}

Modifiers Modifiers::CreateStdModifiers()
{
  Modifiers ret(0,0,0,0,0,0,false,false,false);
  return std::move(ret);
}


Modifiers Modifiers::CreateMIDModifiers(
    const int mismatches,
    const int insertions,
    const int deletions)
{
  Modifiers ret(0,mismatches,insertions,deletions,0,0,false,false,false);
  return std::move(ret);
}
