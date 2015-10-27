//
// Created by Rasmus Fonseca on 25/10/15.
//

#include "sanity_checker.h"

#include <iostream>

namespace SeqScan {

  using ::std::cerr;
  using ::std::endl;

  bool SanityChecker::is_sane(const PTNode *parse_tree)
  {
    std::set<std::string> visited_labels;
    return is_sane(parse_tree, visited_labels);
  }

  //Performs a post-order traversal and sanity-checks. Collects labels on the way to check that backreferences are not
  //forwardreferences (or upreferences).
  bool SanityChecker::is_sane(const PTNode *node, std::set<std::string>& visited_labels)
  {
    switch(node->node_type_){
      case PTNode::kReference:
        if(!check_reference(node, visited_labels)) return false;
        break;
      case PTNode::kComposite:
        if(!check_composite(node, visited_labels)) return false;
        break;
      case PTNode::kSequence:
        if(!check_sequence(node)) return false;
        break;
      case PTNode::kRepeat:
        if(!check_repeat(node, visited_labels)) return false;
        break;
    }

    if( ! node->label_.empty() )
      visited_labels.insert(node->label_);

    return true;

  }

  bool SanityChecker::check_reference(const PTNode *node, std::set<std::string>& visited_labels)
  {
    if( ! node->children_.empty() )
    { cerr<<"Sanity: Reference units can't have children"<<endl; return false; }

    if( node->max_repeats_ || node->min_repeats_ )
    { cerr<<"Sanity: Reference units can't be repeat units"<<endl; return false; }

    if( ! node->sequence_.empty() )
    { cerr<<"Sanity: Reference units can't be sequence units"<<endl; return false; }

    if( node->referenced_label_.empty() )
    { cerr<<"Sanity: Reference units must refer to a nonempty label"<<endl; return false; }

    if( visited_labels.count(node->referenced_label_)==0 )
    { cerr<<"Sanity: The label "<<node->referenced_label_<<" is not defined before its used"<<endl; return false; }

    return true;
  }

  bool SanityChecker::check_sequence(const PTNode *node)
  {
    if( ! node->children_.empty() )
    { cerr<<"Sanity: Sequence units can't have children"<<endl; return false; }

    if( node->max_repeats_ || node->min_repeats_ )
    { cerr<<"Sanity: Sequence units can't be repeat units"<<endl; return false; }

    if( node->sequence_.empty() )
    { cerr<<"Sanity: Sequence units must have a non-empty sequence to match"<<endl; return false; }

    if( !node->referenced_label_.empty() )
    { cerr<<"Sanity: Sequence units can't be reference units"<<endl; return false; }

    return true;
  }

  bool SanityChecker::check_composite(const PTNode *node, std::set<std::string>& visited_labels)
  {
    if( node->children_.empty() )
    { cerr<<"Sanity: Composite units must have children"<<endl; return false; }

    if( node->max_repeats_ || node->min_repeats_ )
    { cerr<<"Sanity: Composite units can't be repeat units"<<endl; return false; }

    if( ! node->sequence_.empty() )
    { cerr<<"Sanity: Composite units can't be sequence units"<<endl; return false; }

    if( ! node->referenced_label_.empty() )
    { cerr<<"Sanity: Composite units can't be reference units"<<endl; return false; }

    // Call is_sane recursively on all children
    for(size_t i=0;i<node->children_.size(); ++i){
      if( !is_sane(node->children_[i], visited_labels) ) return false;
    }

    return true;
  }

  bool SanityChecker::check_repeat(const PTNode *node, std::set<std::string>& visited_labels)
  {
    if( node->children_.size()!=1 )
    { cerr<<"Sanity: Repeat units must have something to repeat"<<endl; return false; }

    if( node->max_repeats_>0 && node->max_repeats_<node->min_repeats_ )
    { cerr<<"Sanity: Repeat units must have min-repeat <= max-repeat"<<endl; return false; }

    if( node->max_repeats_==0 && node->min_repeats_==0 )
    { cerr<<"Sanity: Repeat units can't have min-repeat = max-repeat = 0"<<endl; return false; }

    if( !node->sequence_.empty() )
    { cerr<<"Sanity: Repeat units can't be sequence units"<<endl; return false; }

    if( !node->referenced_label_.empty() )
    { cerr<<"Sanity: Repeat units can't be reference units"<<endl; return false; }

    // Call is_sane recursively on child
    if( !is_sane(node->children_[0], visited_labels) ) return false;

    return true;
  }

}
