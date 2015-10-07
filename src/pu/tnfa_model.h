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

#ifndef PU_TNFA_MODEL_H_
#define PU_TNFA_MODEL_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "tnfa_state.h"
#include "tnfa_start_state.h"
#include "tnfa_final_state.h"
#include "../modifiers.h"

class TNFAModel {
public:
  virtual void Initialize(std::string::const_iterator pos,
                          std::string::const_iterator max_pos,
                          bool stay_at_pos = false) = 0;

  virtual bool FindMatch() = 0;

  virtual const Match& GetMatch() const = 0;
};

#endif  // PU_TNFA_UNIT_H_
