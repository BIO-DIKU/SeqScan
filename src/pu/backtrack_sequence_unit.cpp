#include "backtrack_sequence_unit.h"


BacktrackSequenceUnit::BacktrackSequenceUnit(
    const Modifiers &modifiers,
    const std::string& pattern
) :
    PatternUnit(modifiers),
    pattern_(pattern)
{ }
