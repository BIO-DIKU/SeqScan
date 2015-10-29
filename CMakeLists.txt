cmake_minimum_required (VERSION 2.8)

# About the project
# ------------------------
# Project name
project(SeqScan)

include(ExternalProject)

# Set up pattern parser so it compiles automatically
# ------------------------
set(parser_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/parser")
set(parser_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/parser")
set(parser_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${parser_INSTALL_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR}/parser-generator)
ExternalProject_Add(
	parser
	PREFIX ${parser_PREFIX}
	URL ${CMAKE_CURRENT_SOURCE_DIR}/parser-generator
	INSTALL_DIR ${parser_INSTALL_DIR}
	CMAKE_ARGS ${parser_CMAKE_ARGS}
)



# Options
# ------------------------
# Change default install path
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/bin" CACHE PATH "default install path" FORCE)
endif()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


# Compiler options
# ------------------------
# Thanks to Will Usher for this code snippet:
# http://www.willusher.io/sdl2%20tutorials/2014/03/06/lesson-0-cmake/
#
# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -pedantic-errors -std=c++11")
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -Werror -pedantic-errors -std=c++11")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()


# Executable
# ------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FILE(GLOB SOURCE_FILES src/*.cc src/pu/*.cc src/pu/tnfa/*.cc src/pu_factory/*.cc )
FILE(GLOB HEADER_FILES src/*.h src/pu/*.h src/pu/tnfa/*.h src/pu_factory/*.h )

#https://cmake.org/cmake/help/v3.0/command/include_directories.html
#Enables us to #include "pu/backtrack_unit.h" from files that are in "pu"
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#The parser is compiled in parser-generator. Add include and lib dirs
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser-generator/include)
#link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/parser-generator/lib/libseqscanparser.a)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


# http://stackoverflow.com/questions/16449676/remove-specific-file-from-cmake-build
set(TEST_SOURCE_FILES ${SOURCE_FILES})
list(REMOVE_ITEM TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
list(REMOVE_ITEM TEST_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/run_seqscan.cc)
#list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/run_seqscan.cc)
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_tests.cc)

add_executable(seqscan ${SOURCE_FILES} ${HEADER_FILES})


#Link parser
include_directories(${parser_INSTALL_DIR}/include)
target_link_libraries(seqscan ${parser_INSTALL_DIR}/lib/libSeqScanParser.a)



#Necessary for flex parser
#target_link_libraries(seqscan /usr/local/opt/flex/lib/libfl.a)

# Build tests if CMAKE_BUILD_TYPE=Debug is set
# ------------------------
if (CMAKE_BUILD_TYPE MATCHES DEBUG OR CMAKE_BUILD_TYPE MATCHES "Debug")
    FILE(GLOB TEST_FILES tests/*.cc tests/parser/*.cc tests/pu/*.cc tests/pu/tnfa/*.cc)
    add_executable("seqscan_test" ${TEST_FILES} ${TEST_SOURCE_FILES} ${HEADER_FILES})
	#target_link_libraries(seqscan_test /usr/local/opt/flex/lib/libfl.a)
endif()
