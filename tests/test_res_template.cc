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

#include "catch.h"
#include "../src/res_template.h"

using namespace std;

TEST_CASE("ResTemplate::FileMatrixToTemplate", "[res_template]") {
  SECTION("Unreadable file") {
    // REQUIRE_THROWS_AS();
  }

  SECTION("Bad format") {
    // REQUIRE_THROWS_AS();
  }

  SECTION("OK MatrixBad format") {
    // REQUIRE();
  }
}

TEST_CASE("ResTemplate::MatrixToTemplate", "[res_template]") {
  ResTemplate res_template(8);

  REQUIRE(res_template.is_set('A' << kSizeOfChar | 'N'));
  REQUIRE(res_template.is_set('N' << kSizeOfChar | 'A'));
}
