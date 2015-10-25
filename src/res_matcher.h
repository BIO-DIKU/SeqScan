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

#include "res_template.h"
#include <bitset>

/**
 * @brief Class for matching residues using a residue template with encoded
 * information on which residue pairs match.
 *
 * @param Residue template.
 */
class ResMatcher {
 public:
  ResMatcher(ResTemplate res_template);

  ~ResMatcher();

  /**
   * Match two residues and return true if they match according to the
   * res_template.
   *
   * @param a First residue
   * @parem b Second residue
   */
  bool match(char a, char b);

 private:

  std::bitset<65536> res_template_;  // FIXME(Martin): Avaid hard coded value
};
