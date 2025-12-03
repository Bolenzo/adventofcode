cmake_minimum_required(VERSION 4.0)

project(aoc
  DESCRIPTION "Bolenzo's Advent of Code C++ Solutions"
  LANGUAGES CXX
  VERSION 2025.0.0
)

# Declare warnings used by this project.
# TODO: remove warnings from project: provide them from outside instead,
# possibly putting them in toolchain files for convenience.
add_library(aoc.project_warnings INTERFACE)
add_library(aoc::project_warnings ALIAS aoc.project_warnings)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(aoc.project_warnings)

set(BUILD_SHARED_LIBS OFF)

option(AOC_VERIFY_HEADERS
  "Verify that headers can be included on their own. Default: ${PROJECT_IS_TOP_LEVEL}. Values: {ON, OFF}."
  ${PROJECT_IS_TOP_LEVEL}
)
if(AOC_VERIFY_HEADERS)
  # NB: we want headers to be verified automatically when the 'all' target is
  # built; however, the 'all_verify_interface_header_sets' target created by
  # cmake is not part of 'all', so we need to define a custom target that is
  # part of 'all' and depends on 'all_verify_interface_header_sets'.
  add_custom_target(aoc_verify_headers ALL
    DEPENDS all_verify_interface_header_sets
  )
endif()
option(AOC_BUILD_TESTS
  "Enable building tests and test infrastructure. Default: ${PROJECT_IS_TOP_LEVEL}. Values: {ON, OFF}."
  ${PROJECT_IS_TOP_LEVEL}
)
if(AOC_BUILD_TESTS)
  add_subdirectory(aoc/unit_test)
endif()

enable_testing()

add_subdirectory(aoc/core)
