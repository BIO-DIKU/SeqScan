
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
