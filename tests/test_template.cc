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

TEST_CASE( "Test case name", "[tag1,tag2]" ) {

	// Test setup.

  int actual = 5, expected = 5;

  REQUIRE( actual >= expected );
  REQUIRE( actual == expected );
  REQUIRE( actual <= expected );

  SECTION( "section description" ) {
    // Perform action

    // Expected bahavior
    REQUIRE( actual == expected );
  }

}


// Example test of vector class. Notice that before each section the size is 5
//
// TEST_CASE( "vectors can be sized and resized", "[vector]" ) {
//
//     std::vector<int> v( 5 );
//
//     REQUIRE( v.size() == 5 );
//     REQUIRE( v.capacity() >= 5 );
//
//     SECTION( "resizing bigger changes size and capacity" ) {
//         v.resize( 10 );
//
//         REQUIRE( v.size() == 10 );
//         REQUIRE( v.capacity() >= 10 );
//     }
//     SECTION( "resizing smaller changes size but not capacity" ) {
//         v.resize( 0 );
//
//         REQUIRE( v.size() == 0 );
//         REQUIRE( v.capacity() >= 5 );
//     }
//     SECTION( "reserving bigger changes capacity but not size" ) {
//         v.reserve( 10 );
//
//         REQUIRE( v.size() == 5 );
//         REQUIRE( v.capacity() >= 10 );
//     }
//     SECTION( "reserving smaller does not change size or capacity" ) {
//         v.reserve( 0 );
//
//         REQUIRE( v.size() == 5 );
//         REQUIRE( v.capacity() >= 5 );
//     }
// }
