###############################################################################
# Library target
###############################################################################
add_library(aoc.core)
add_library(aoc::core ALIAS aoc.core)

target_sources(aoc.core PUBLIC
  FILE_SET HEADERS
  BASE_DIRS ${PROJECT_SOURCE_DIR}
  FILES getline_view.hpp
)
target_sources(aoc.core PRIVATE
  getline_view.cpp
)
set_target_properties(aoc.core PROPERTIES
  VERIFY_INTERFACE_HEADER_SETS ${AOC_VERIFY_HEADERS}
)
target_link_libraries(aoc.core PRIVATE
  aoc::project_warnings
)

###############################################################################
# Unit test target
###############################################################################
if (NOT AOC_BUILD_TESTS)
  return()
endif()

add_executable(aoc.core.tests)
target_sources(aoc.core.tests PRIVATE
  getline_view.test.cpp
)
target_link_libraries(aoc.core.tests PRIVATE
  aoc::core
  aoc::unit_test
  aoc::project_warnings
)
aoc_add_tests(aoc.core.tests "core")
