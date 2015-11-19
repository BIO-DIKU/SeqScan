cmake_minimum_required (VERSION 2.8)

# About the project
# ------------------------
# Project name
project(SeqScanParser)


# Options
# ------------------------
# Change default install path
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/bin" CACHE PATH "default install path" FORCE)
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Source and header files
# ------------------------
FILE(GLOB SOURCE_FILES src/*.cc )
FILE(GLOB HEADER_FILES src/*.h )

list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)


# Use flex and bison to compile .l and .y files 
# ------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX REQUIRED)
BISON_TARGET(MyParser ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/src/scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set (BISON_EXTRA_HEADERS
  ${CMAKE_CURRENT_BINARY_DIR}/position.hh
  ${CMAKE_CURRENT_BINARY_DIR}/Location.hh
  ${CMAKE_CURRENT_BINARY_DIR}/stack.hh
)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${BISON_EXTRA_HEADERS}")

list(APPEND SOURCE_FILES ${FLEX_MyScanner_OUTPUT_SOURCE})
list(APPEND HEADER_FILES ${FLEX_MyScanner_OUTPUT_HEADER})
list(APPEND SOURCE_FILES ${BISON_MyParser_OUTPUT_SOURCE})
list(APPEND HEADER_FILES ${BISON_MyParser_OUTPUT_HEADER})


set(LIB_NAME ${PROJECT_NAME})
add_library(${LIB_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_executable(runparser ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_libraries(runparser ${LIB_NAME})


# Executable
# ------------------------
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#add_executable(runparser ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
#link_libraries(seqscanparser)

# Install instructions
# ------------------------
#install(FILES src/parse_tree_unit.h src/interpreter.h DESTINATION include/parser)
#install(DIRECTORY src/ DESTINATION include/parser FILES_MATCHING PATTERN "*.h")
message("PARSER HEADERS: ${HEADER_FILES}")
install(FILES ${HEADER_FILES} ${BISON_EXTRA_HEADERS} DESTINATION include/parser)
install(TARGETS ${LIB_NAME} DESTINATION lib)

