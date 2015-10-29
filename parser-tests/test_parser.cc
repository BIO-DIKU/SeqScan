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

// =============== Sequence =============== 
TEST_CASE( "Parsing sequence", "parser" ) {

  SeqScan::Interpreter i;

  SECTION( "A single valid sequence" ) {
    SeqScan::ParseTreeUnit* ptree;
    REQUIRE_NOTHROW(ptree = i.parse("ACTUNGactung")); //All DNA/RNA characters mixed
    REQUIRE( ptree->repr() == "(SEQ)" );

    REQUIRE_NOTHROW(ptree = i.parse("A")); // Single character
    REQUIRE( ptree->repr() == "(SEQ)" );
  }

  SECTION( "A single invalid sequence" ) {
    //Some of these are neither DNA/RNA/prot
    REQUIRE_THROWS_AS(i.parse("abcdefghijklmnopqrstu"), SeqScan::PatternParseException); 
  }

}


// =============== Reference ============== 
TEST_CASE( "Parsing reference", "parser" ) {

  SeqScan::Interpreter i;

  SECTION( "A single valid reference" ) {
    SeqScan::ParseTreeUnit* ptree;
    REQUIRE_NOTHROW(ptree = i.parse("p1"));                                //Should fail in sanity checker
    REQUIRE( ptree->repr() == "(REF)" );
    REQUIRE( ptree->children_[0]->referenced_label_ == "p1" );

    REQUIRE_NOTHROW(ptree = i.parse("lbl_12"));                            //Single underscore is ok
    REQUIRE( ptree->repr() == "(REF)" );
    REQUIRE( ptree->children_[0]->referenced_label_ == "lbl_12" );
  }

  SECTION( "Reference with modifiers" ) {
    SeqScan::ParseTreeUnit* ptree;
    REQUIRE_NOTHROW(ptree = i.parse("p2=<~p1/1,2,3"));                        //Complement ref
    REQUIRE( ptree->repr() == "(REF)" );
    REQUIRE( ptree->children_[0]->label_ == "p2" );
    REQUIRE( ptree->children_[0]->pre_modifier_.tilde_ == true );
    REQUIRE( ptree->children_[0]->pre_modifier_.less_ == true );
    REQUIRE( ptree->children_[0]->suf_modifier_.mismatches_ == 1 );
    REQUIRE( ptree->children_[0]->suf_modifier_.insertions_ == 2 );
    REQUIRE( ptree->children_[0]->suf_modifier_.deletions_  == 3 );
  }

  SECTION( "An invalid reference" ) {
    REQUIRE_THROWS_AS(i.parse("_lbl_12"), SeqScan::PatternParseException); //Only one _ allowed
    REQUIRE_THROWS_AS(i.parse("lbl12a"), SeqScan::PatternParseException);  //Must be chars followed by ints
    REQUIRE_THROWS_AS(i.parse("12_lbl"), SeqScan::PatternParseException);  //Must be chars followed by ints
  }
}


// ================= Range ================
TEST_CASE( "Parsing range", "parser" ) {

  SeqScan::Interpreter i;

  SECTION( "A single range" ) {
    SeqScan::ParseTreeUnit* ptree;
    REQUIRE_NOTHROW(ptree = i.parse("1..2"));
    REQUIRE( ptree->repr() == "(RANGE)" );
    REQUIRE( ptree->children_[0]->range_min_ == 1 );
    REQUIRE( ptree->children_[0]->range_max_ == 2 );

    REQUIRE_NOTHROW(ptree = i.parse("2...3"));
    REQUIRE( ptree->repr() == "(RANGE)" );
    REQUIRE( ptree->children_[0]->range_min_ == 2 );
    REQUIRE( ptree->children_[0]->range_max_ == 3 );

    REQUIRE_THROWS_AS(i.parse("2.3"), SeqScan::PatternParseException);
    REQUIRE_THROWS_AS(i.parse("2....3"), SeqScan::PatternParseException);

    //Equivalent to range, but not a range. Any conversion should happen in factory
    REQUIRE_NOTHROW(ptree = i.parse("N{1,2}"));           
    REQUIRE( ptree->repr() == "(REP(SEQ))" );
  }
}

// ================= Group ================
//TODO: Add tests
// =============== Composite ==============
//TODO: Add tests
// ================== Or ==================
//TODO: Add tests
// ================ Repeat ================
//TODO: Add tests
//
//
// ============ Absurd patterns ===========
//TODO: Check that "4" fails

