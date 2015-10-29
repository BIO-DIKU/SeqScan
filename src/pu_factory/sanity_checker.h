//
// Created by Rasmus Fonseca on 25/10/15.
//

#ifndef SEQSCAN_SANITY_CHECKER_H
#define SEQSCAN_SANITY_CHECKER_H

#include <set>
#include <string>

#include <parser/parse_tree_unit.h>

namespace SeqScan {

  class SanityChecker {

   public:

    /**
     * Performs sanity checks on the specified parse tree. Prints errors to cerr and returns false if anything appears
     * that will make the search with PatternUnit break down.
     */
    bool is_sane(const ParseTreeUnit *parse_tree);

   private:
    bool is_sane(const ParseTreeUnit *parse_tree, std::set<std::string>& visited_labels);

    bool check_reference(const ParseTreeUnit *node, std::set<std::string>& visited_labels);
    bool check_sequence(const ParseTreeUnit *node);
    bool check_composite(const ParseTreeUnit *node, std::set<std::string>& visited_labels);
    bool check_repeat(const ParseTreeUnit *node);

  };

} // namespace SeqScan

#endif //SEQSCAN_SANITY_CHECKER_H
