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
	for (size_t i = 0; i < children_.size(); ++i) {
		delete children_[i];
	}
}

std::string ParseTreeUnit::Str(size_t indent) const {
    std::stringstream ts;

    for (size_t i = 0; i < indent; ++i) ts << " ";
    ts << "ParseTreeUnit[" << node_type_;

    if (!label_.empty())
      ts << ",lbl=" << label_;

    if (!children_.empty()) {
      ts << ",children=(";

      for (size_t i = 0; i < children_.size(); i++) {
        ts << std::endl;

        ts << children_[i]->Str(indent + 2);
      }

      ts << ")";
    }

    if (node_type_ == UnitType::Sequence) {
      ts << ",seq=" << sequence_;
    }

    if (node_type_ == UnitType::Repeat) {
      ts << ",rep={" << min_repeats_ << "," << max_repeats_ << "}";
    }

    if (node_type_ == UnitType::Reference) {
      ts << ",ref=" << referenced_label_;
    }

    std::string pre = pre_modifier_.str();

    if (!pre.empty()) {
      ts << ",pre_mod=" << pre;
		}

    std::string suf = suf_modifier_.str();

    if (!suf.empty()) {
      ts << ",suf_mod=" << suf;
		}

    ts << "]";

    return ts.str();
}

std::string ParseTreeUnit::Repr() const {
  std::stringstream ss;
  switch(node_type_){
    case UnitType::Sequence:  return "SEQ";
    case UnitType::Reference: return "REF";
    case UnitType::Range:     return "RANGE";
    case UnitType::Group:     return "GROUP";
    case UnitType::Composite:
      ss << "(";

      for (size_t i = 0; i < children_.size(); ++i) {
        if (i > 0) ss << ",";
        ss << children_[i]->Repr();
      }

      ss << ")";

      return ss.str();
    case UnitType::Or:
      ss << "OR(";

      for (size_t i = 0; i < children_.size(); ++i) {
        if (i > 0) ss << ",";
        ss << children_[i]->Repr();
      }

      ss << ")";

      return ss.str();
    case UnitType::Repeat:
      ss << "REP(";
      ss << children_[0]->Repr();
      ss << ")";
      return ss.str();
  }
  return "";
}

void ParseTreeUnit::AddModifier(PTSufModifier *m)
{
  suf_modifier_.mismatches_  += m->mismatches_;
  suf_modifier_.insertions_  += m->insertions_;
  suf_modifier_.deletions_   += m->deletions_;
  suf_modifier_.indels_      += m->indels_;
  suf_modifier_.errors_      += m->errors_;
}

void ParseTreeUnit::AddModifier(PTPreModifier *m)
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

  if (hat_)
    ss << "^";
  if (tilde_)
    ss << "~";
  if (less_)
    ss << "<";
  if (hat_)
    ss << "^";
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
  if (insertions_ > 0 || deletions_ > 0)
    ss << "/" << mismatches_ << "," << insertions_ << "," << deletions_;
  else if (indels_ > 0)
    ss << "/" << mismatches_ << "," << indels_;
  else if (errors_ > 0)
    ss << "/" << errors_;
  else if (mismatches_ > 0)
    ss << "/" << mismatches_ << ",0";
  return ss.str();
}
} // namespace seqscan
