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

#include "tnfa_unit.h"
#include "tnfa_model_512.h"
#include "tnfa_model_64.h"

TNFAUnit::TNFAUnit(const Modifiers &modifiers, const std::string pattern)
  : PatternUnit(modifiers), pattern_(pattern)
{
  if(modifiers.insertions_ > 3 || modifiers.insertions_ > 3 || modifiers.deletions_ > 3)
    model_ = new TNFAModel512(modifiers, pattern);
  else
    model_ = new TNFAModel64(modifiers, pattern);
}

void TNFAUnit::Initialize(std::string::const_iterator pos,
                          std::string::const_iterator max_pos,
                          bool stay_at_pos ) {
  model_->Initialize(pos, max_pos, stay_at_pos);
}

bool TNFAUnit::FindMatch() {
  return model_->FindMatch();
}

const Match& TNFAUnit::GetMatch() const
{ return model_->GetMatch(); }

std::ostream& TNFAUnit::Print(std::ostream &os) const
{
  modifiers_.PrintPUPrefix(os);
  os<<pattern_;
  modifiers_.PrintPUSuffix(os);

  return os;
}
