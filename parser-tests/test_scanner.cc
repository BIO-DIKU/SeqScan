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

#include <interpreter.h>

TEST_CASE( "Every valid character recognized", "scanner" ) {

  SeqScan::Interpreter i;

  SECTION( "Big pattern with all valid characters" ) {

    SeqScan::ParseTreeUnit* ptree;
    REQUIRE_NOTHROW(ptree = i.parse("^p1=ACTUNGactung{2,3}/2,1,0 <~p1+| (N{2}* [^AC]){2,}$"));
    REQUIRE( ptree != NULL );
  }

}

TEST_CASE( "Invalid patterns", "scanner" ) {

  SeqScan::Interpreter i;

  SECTION( "Unrecognized symbols" ) {
    REQUIRE_THROWS_AS(i.parse("AA ! AA"), SeqScan::PatternParseException);
    REQUIRE_THROWS_AS(i.parse(">AA"), SeqScan::PatternParseException);
  }

  SECTION( "Usable symbols in wrong context" ){
    REQUIRE_THROWS_AS(i.parse("AA _ AA"), SeqScan::PatternParseException);
    REQUIRE_THROWS_AS(i.parse("AA _p1=AA"), SeqScan::PatternParseException);
    REQUIRE_NOTHROW(i.parse("AA p_1=AA"));
    REQUIRE_THROWS_AS(i.parse("AA _ AA"), SeqScan::PatternParseException);
    REQUIRE_THROWS_AS(i.parse("AA |  AA"), SeqScan::PatternParseException); //Two spaces
    REQUIRE_NOTHROW(i.parse("AA | AA"));
  }

}


