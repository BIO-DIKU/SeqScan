/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "sanity_checker.h"

#include <iostream>

namespace SeqScan {

using ::std::cerr;
using ::std::endl;

bool SanityChecker::IsSane(const ParseTreeUnit *parse_tree)
{
  std::set<std::string> visited_labels;
  return IsSane(parse_tree, visited_labels);
}

//Performs a post-order traversal and sanity-checks. Collects labels on the way to check that backreferences are not
//forwardreferences (or upreferences, e.g. 'p1=(AAT p1)').
bool SanityChecker::IsSane(const ParseTreeUnit *node, std::set<std::string> &visited_labels)
{
  switch(node->node_type_){
    case ParseTreeUnit::UnitType::Reference:
      if(!CheckReferences(node, visited_labels)) return false;
      break;
    case ParseTreeUnit::UnitType::Composite:
      if(!CheckComposite(node, visited_labels)) return false;
      break;
    case ParseTreeUnit::UnitType::Sequence:
      if(!CheckSequence(node)) return false;
      break;
    case ParseTreeUnit::UnitType::Repeat:
      if(!CheckRepeat(node, visited_labels)) return false;
      break;
  }

  if( ! node->label_.empty() )
    visited_labels.insert(node->label_);

  return true;

}

bool SanityChecker::CheckReferences(const ParseTreeUnit *node, std::set<std::string> &visited_labels)
{

  if( node->referenced_label_.empty() )
  { cerr<<"Sanity: Reference units must refer to a nonempty label"<<endl; return false; }

  if( visited_labels.count(node->referenced_label_)==0 )
  { cerr<<"Sanity: The label "<<node->referenced_label_<<" is not defined before its used"<<endl; return false; }

  return true;
}

bool SanityChecker::CheckSequence(const ParseTreeUnit *node)
{
  if( node->sequence_.empty() )
  { cerr<<"Sanity: Sequence units must have a non-empty sequence to match"<<endl; return false; }

  return true;
}

bool SanityChecker::CheckComposite(const ParseTreeUnit *node, std::set<std::string> &visited_labels)
{
  if( node->children_.empty() )
  { cerr<<"Sanity: Composite units must have children"<<endl; return false; }

  // Call IsSane recursively on all children
  for(size_t i=0;i<node->children_.size(); ++i){
    if( !IsSane(node->children_[i], visited_labels) ) return false;
  }

  return true;
}

bool SanityChecker::CheckRepeat(const ParseTreeUnit *node, std::set<std::string> &visited_labels)
{
  if( node->children_.size()!=1 )
  { cerr<<"Sanity: Repeat units must have something to repeat"<<endl; return false; }

  if( node->max_repeats_>0 && node->max_repeats_<node->min_repeats_ )
  { cerr<<"Sanity: Repeat units must have min-repeat <= max-repeat"<<endl; return false; }

  if( node->max_repeats_==0 && node->min_repeats_==0 )
  { cerr<<"Sanity: Repeat units can't have min-repeat = max-repeat = 0"<<endl; return false; }

  // Call IsSane recursively on child
  if( !IsSane(node->children_[0], visited_labels) ) return false;

  return true;
}

}
