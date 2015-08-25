#ifndef MODIFIERS_H
#define MODIFIERS_H


class Modifiers {

public:
    Modifiers(
            const int max_edits,
            const int mismatches,
            const int insertions,
            const int deletions,
            const int min_repeats,
            const int max_repeats,
            const bool reverse,
            const bool complement,
            const bool greedy
    );

    const int max_edits_;
    const int mismatches_;
    const int insertions_;
    const int deletions_;
    const int min_repeats_;
    const int max_repeats_;
    const bool reverse_;
    const bool complement_;
    const bool greedy_;
};


#endif //SEQSCAN_MODIFIERS_H
