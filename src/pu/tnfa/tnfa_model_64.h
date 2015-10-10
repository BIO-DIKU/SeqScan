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

#ifndef PU_TNFA_MODEL_64_H_
#define PU_TNFA_MODEL_64_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "tnfa_state_64.h"
#include "tnfa_model.h"

class TNFAModel64 : public TNFAModel {
public:

  TNFAModel64(const Modifiers &modifiers, const std::string& pattern);

  void Initialize(std::string::const_iterator pos,
                  std::string::const_iterator max_pos,
                  bool stay_at_pos = false);

  bool FindMatch();

  const Match& GetMatch() const;

  // Create error codes from m,i,d modifiers
  void ModifiersToErrorCode(const Modifiers &modifiers);

  std::ostream& Print(std::ostream &os) const;
private:
  TNFAState64                  *startState_;
  uint64_t                     errorCode_;
  std::vector< TNFAState64 * > stateLists_[ 2 ];
};

#endif  // PU_TNFA_UNIT_H_
