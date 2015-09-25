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

#include <assert.h>
#include "reference_unit.h"
#include "backtrack_unit.h"

ReferenceUnit::ReferenceUnit( PatternUnit* pu, const Modifiers &modifiers ):
    PatternUnit(modifiers),
    referenced_unit_(pu)
{
}

void ReferenceUnit::Initialize(
    std::string::const_iterator pos,
    std::string::const_iterator max_pos,
    bool stay_at_pos
)
{
  const Match& match = referenced_unit_->GetMatch();
  std::string pattern(match.pos, match.pos+match.len);
  pattern_finder_ = std::unique_ptr<PatternUnit>( new BacktrackUnit(modifiers_, pattern) );
  pattern_finder_->Initialize(pos, max_pos, stay_at_pos);
}

bool ReferenceUnit::FindMatch()
{
  return pattern_finder_->FindMatch();
}

const Match& ReferenceUnit::GetMatch() const
{
  return pattern_finder_->GetMatch();
}

std::ostream& ReferenceUnit::Print(std::ostream &os) const
{
  modifiers_.PrintPUPrefix(os);

  os<<referenced_unit_->modifiers_.label_;

  modifiers_.PrintPUSuffix(os);
  return os;
}

std::unique_ptr<PatternUnit> ReferenceUnit::Clone() const
{
  std::unique_ptr<PatternUnit> ret =
      std::unique_ptr<PatternUnit>(
          new ReferenceUnit(referenced_unit_,modifiers_)
      );

  return ret;
}
