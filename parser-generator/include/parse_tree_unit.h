/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef PARSE_TREE_UNIT_H
#define PARSE_TREE_UNIT_H

#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

namespace SeqScan {


  class PTPreModifier{
   public:
    PTPreModifier();

    bool tilde_;
    bool hat_;
    bool less_;
    bool start_anchor_;

    std::string str() const;
  };

  class PTSufModifier{
   public:
    PTSufModifier();

    int mismatches_;
    int insertions_;
    int deletions_;
    int indels_;
    int errors_;
    bool end_anchor_;

    std::string str() const;
  };

  class ParseTreeUnit
  {
   public:
    ParseTreeUnit(const UnitType type);
    ParseTreeUnit(const std::string &sequence);
    ~ParseTreeUnit();

    std::string str(size_t indent) const;

    const UnitType node_type_;

    std::vector<ParseTreeUnit*> children_;

    std::string sequence_;

    std::string label_;

    std::string referenced_label_;

    int min_repeats_;
    int max_repeats_;

    int range_min_;
    int range_max_;

    enum UnitType {
      Composite, Sequence, Repeat, Reference, Range, Or, Group
    }
    //static const int kComposite  = 0;
    //static const int kSequence   = 1;
    //static const int kRepeat     = 2;
    //static const int kReference  = 3;
    //static const int kRange      = 4;
    //static const int kOr         = 5;
    //static const int kGroup      = 6;

    void add_modifier(PTPreModifier* m);
    void add_modifier(PTSufModifier* m);

    PTPreModifier pre_modifier_;
    PTSufModifier suf_modifier_;

  };


} // namespace SeqScan

#endif // COMMAND_H
