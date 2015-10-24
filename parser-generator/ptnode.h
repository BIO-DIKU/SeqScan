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

#ifndef PTNODE_H
#define PTNODE_H

#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

namespace EzAquarii {

class PTPreModifier{
  public:
    PTPreModifier():
      reverse_(false),
      complement_(false) {}

    bool reverse_;
    bool complement_;

    std::string str() const
    {
      std::stringstream ss;
      if(reverse_ && complement_)
        ss<<"~";
      else if(reverse_)
        ss<<"<";
      else if(complement_)
        ss<<"<~";
      return ss.str();
    }
};

class PTSufModifier{
  public:
    PTSufModifier():
      mismatches_(0),
      insertions_(0),
      deletions_(0),
      indels_(0),
      errors_(0) {}

    int mismatches_;
    int insertions_;
    int deletions_;
    int indels_;
    int errors_;

    std::string str() const
    {
      std::stringstream ss;
      if(insertions_>0 || deletions_>0)
        ss<<"/"<<mismatches_<<","<<insertions_<<","<<deletions_;
      else if(indels_>0)
        ss<<"/"<<mismatches_<<","<<indels_;
      else if(errors_>0)
        ss<<"/"<<errors_;
      else if(mismatches_>0)
        ss<<"/"<<mismatches_<<",0";
      return ss.str();
    }
};

class PTNode
{
  public:
    PTNode(const int type);
    PTNode(const std::string &sequence);
    ~PTNode();

    std::string str() const;

    const int node_type_;
    std::vector<PTNode*> children_;
    std::string sequence_;
    std::string label_;
    std::string referenced_label_;
    int min_repeats_;
    int max_repeats_;

    static const int kComposite = 0;
    static const int kSequence = 1;
    static const int kRepeat = 2;
    static const int kReference = 3;
    
    void add_modifier(PTPreModifier* m);
    void add_modifier(PTSufModifier* m);
  private:
    PTPreModifier pre_modifier_;
    PTSufModifier modifier_;

};


}

#endif // COMMAND_H
