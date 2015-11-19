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

#ifndef SEQSCAN_PU_FACTORY_PATTERN_UNIT_FACTORY_H_
#define SEQSCAN_PU_FACTORY_PATTERN_UNIT_FACTORY_H_

#include <map>
#include <string>

#include <parser/parse_tree_unit.h>

#include "pu/pattern_unit.h"
#include "modifiers.h"
#include "res_matcher.h"

namespace SeqScan {
using ::std::string;
using ::std::map;

class PatternUnitFactory {
 public:
  PatternUnitFactory(const ResMatcher& res_matcher, const ResMatcher& res_matcher_comp);

  std::unique_ptr<PatternUnit> CreateFromParseTree(const ParseTreeUnit *ptree);

 private:
  std::unique_ptr<PatternUnit> CreateFromNode(const ParseTreeUnit *node, map<string, PatternUnit *> &ref_map);

  Modifiers CreateModifiers(const ParseTreeUnit *node);

  const ResMatcher& res_matcher_;
  const ResMatcher& res_matcher_comp_;

};
}  // namespace SeqScan

#endif  // SEQSCAN_PU_FACTORY_PATTERN_UNIT_FACTORY_H_
