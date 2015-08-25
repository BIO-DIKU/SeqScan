
cmake_minimum_required (VERSION 2.8.8)

project(seqscan)

set(SEQSCAN_MAJOR_VERSION 0)
set(SEQSCAN_MINOR_VERSION 2)
set(SEQSCAN_VERSION ${SEQSCAN_MAJOR_VERSION}.${SEQSCAN_MINOR_VERSION})


# Enable C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


#add_library(seqscan-lib
add_library(libseqscan
	match.h
	pu/pattern_unit.h
	pu/composite_unit.h

	pu/pattern_unit.cc
	pu/composite_unit.cc
	)

set_target_properties( libseqscan PROPERTIES PREFIX "" )

add_executable( seqscan run_seqscan.cc )
target_link_libraries( seqscan libseqscan )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )
