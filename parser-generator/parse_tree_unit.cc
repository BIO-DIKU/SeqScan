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

#include "parse_tree_unit.h"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

namespace SeqScan {

ParseTreeUnit::ParseTreeUnit(const UnitType type) :
	node_type_(type)
{
}

ParseTreeUnit::ParseTreeUnit(const std::string &sequence):
	node_type_(UnitType::Sequence),
	sequence_(sequence)
{
}

ParseTreeUnit::~ParseTreeUnit()
{
	for(size_t i=0;i<children_.size();++i){
		delete children_[i];
	}
}
    
std::string ParseTreeUnit::str(size_t indent) const {
    std::stringstream ts;

    for(size_t i=0;i<indent;++i) ts<<" ";
    ts << "ParseTreeUnit[" << node_type_;
    
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
    if(node_type_==UnitType::Sequence){
      ts<<",seq="<<sequence_;
    }
    if(node_type_==UnitType::Repeat){
      ts<<",rep={"<<min_repeats_<<","<<max_repeats_<<"}";
    }
    if(node_type_==UnitType::Reference){
      ts<<",ref="<<referenced_label_;
    }
    
    std::string pre = pre_modifier_.str();
    if(!pre.empty())
      ts << ",pre_mod="<<pre;

    std::string suf = suf_modifier_.str();
    if(!suf.empty())
      ts << ",suf_mod="<<suf;

    ts<<"]";
    return ts.str();
}

void ParseTreeUnit::add_modifier(PTSufModifier* m)
{
  suf_modifier_.mismatches_  += m->mismatches_;
  suf_modifier_.insertions_  += m->insertions_;
  suf_modifier_.deletions_   += m->deletions_;
  suf_modifier_.indels_      += m->indels_;
  suf_modifier_.errors_      += m->errors_;
}

void ParseTreeUnit::add_modifier(PTPreModifier* m)
{
  pre_modifier_.tilde_        = m->tilde_;
  pre_modifier_.hat_          = m->hat_;
  pre_modifier_.less_         = m->less_;
  pre_modifier_.start_anchor_ = m->start_anchor_;
}


// ---------------- class PTPreModifier ------------------ 

PTPreModifier::PTPreModifier():
  tilde_(false),
  hat_(false),
  less_(false),
  start_anchor_(false)
{}


std::string PTPreModifier::str() const
{
  std::stringstream ss;
  if(hat_)
    ss<<"^";
  if(tilde_)
    ss<<"~";
  if(less_)
    ss<<"<";
  if(hat_)
    ss<<"^";
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
