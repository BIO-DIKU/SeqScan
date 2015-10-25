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

#include <bitset>

/**
 * @brief Class for creating a match template, which contians specification on
 * matching residue pairs. The match template consists of a bitset and the index
 * of matching residues pairs are set by concatenating the char bits. So for the
 * matching residue pair T-U the binary representations are:
 *
 * T:          0000000001010100 = 84
 * U:          0000000001010101 = 85
 * T << 8 | U: 0101010001010101 = 21589
 *
 * We use the index position 21589 to indicate that T-U is a matching residue
 * pair.
 */
class ResTemplate {
 public:
  /*
   * Predifined templates.
   */
  ResTemplate(int template_num);

  /*
   * Custom templates from file.
   */
  ResTemplate(std::string template_file);

  /*
   * Create a match template from a vector of match pairs i.e. two char strings.
   */
  ResTemplate(std::vector<std::string> match_pairs);

  ~ResTemplate();

 private:

  /*
   * Residue template.
   */
  std::bitset<65536> res_template_;

  /*
   * Create a match template from a vector of match pairs i.e. two char strings.
   */
  void ResTemplate::MatchPairsToTemplate();
};
