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

#include "ptnode.h"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

namespace SeqScan {

PTNode::PTNode(int type) :
	node_type_(type)
{
}

PTNode::PTNode(const std::string &sequence):
	node_type_(PTNode::kSequence),
	sequence_(sequence)
{
}

PTNode::~PTNode()
{
	for(size_t i=0;i<children_.size();++i){
		delete children_[i];
	}
}
    
std::string PTNode::str(size_t indent) const {
    std::stringstream ts;

    for(size_t i=0;i<indent;++i) ts<<" ";
    ts << "PTNode[" << node_type_;
    
    if(!label_.empty())
      ts << ",lbl=" << label_;

    if(!children_.empty()){
      ts<<",children=(";

      for(size_t i = 0; i < children_.size(); i++) {
        //if(i>0) ts<<" ";
        ts<<std::endl;

        ts<<children_[i]->str(indent+2);
      }
      ts<<")";
    }
    if(node_type_==PTNode::kSequence){
      ts<<",seq="<<sequence_;
    }
    if(node_type_==PTNode::kRepeat){
      ts<<",rep={"<<min_repeats_<<","<<max_repeats_<<"}";
    }
    if(node_type_==PTNode::kReference){
      ts<<",ref="<<referenced_label_;
    }
    
    std::string pre = pre_modifier_.str();
    if(!pre.empty())
      ts << ",pre_mod="<<pre;

    std::string suf = modifier_.str();
    if(!suf.empty())
      ts << ",suf_mod="<<suf;

    ts<<"]";
    return ts.str();
}

void PTNode::add_modifier(PTSufModifier* m)
{
  modifier_.mismatches_  += m->mismatches_;
  modifier_.insertions_  += m->insertions_;
  modifier_.deletions_   += m->deletions_;
  modifier_.indels_      += m->indels_;
  modifier_.errors_      += m->errors_;
}

void PTNode::add_modifier(PTPreModifier* m)
{
  pre_modifier_.reverse_    = m->reverse_;
  pre_modifier_.complement_ = m->complement_;
}


// ---------------- class PTPreModifier ------------------ 

PTPreModifier::PTPreModifier():
  reverse_(false),
  complement_(false) 
{}


std::string PTPreModifier::str() const
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


// ---------------- class PTSufModifier ------------------

PTSufModifier::PTSufModifier():
  mismatches_(0),
  insertions_(0),
  deletions_(0),
  indels_(0),
  errors_(0) 
{}

std::string PTSufModifier::str() const
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







} // namespace seqscan