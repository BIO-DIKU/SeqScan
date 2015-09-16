
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
  modifiers.h
  pu/pattern_unit.h
  pu/composite_unit.h
  pu/backtrack_unit.h
  pu/tnfa_unit.h
  pu/tnfa_state.h
  pu/tnfa_final_state.h
  pu/tnfa_start_state.h

  pu/pattern_unit.cc
  pu/composite_unit.cc
  modifiers.cc 
  pu/backtrack_unit.cc 
  pu/tnfa_unit.cc
  pu/tnfa_state.cc
  pu/tnfa_final_state.cc pu/repeat_unit.cc pu/repeat_unit.h io.cc io.h match.cc pu/reference_unit.cc pu/reference_unit.h pu/range_unit.cc pu/range_unit.h)

set_target_properties( libseqscan PROPERTIES PREFIX "" )

add_executable( seqscan run_seqscan.cc )
target_link_libraries( seqscan libseqscan )

# Test executable
add_executable( seqscan_unittests 
  tests/run_tests.cc
  tests/test_fuzzy_sequence.cc
  tests/test_backtrack_unit.cc
  tests/test_composite_unit.cc
  tests/test_tnfa_unit.cc)
  
target_link_libraries( seqscan_unittests libseqscan )

enable_testing()
add_test(UnitTests seqscan_unittests)

#From http://stackoverflow.com/questions/16158091/cmake-setting-an-environmental-variable-for-ctest-or-otherwise-getting-failed
if (CMAKE_CONFIGURATION_TYPES)
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
    --force-new-ctest-process --output-on-failure 
    --build-config "$<CONFIGURATION>")
else()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} 
    --force-new-ctest-process --output-on-failure)
endif()

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )
