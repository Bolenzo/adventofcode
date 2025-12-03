if(NOT COMMAND catch_discover_tests)
  include(Catch)
  if(NOT COMMAND catch_discover_tests)
    message(FATAL_ERROR "'catch_discover_tests' not available: make sure 'Catch2' is included as a dependency.")
  endif()
endif()

# The command 'aoc_add_tests' is a wrapper around 'catch_discover_tests' that
# helps adding to 'ctest' tests related to the specified 'TARGET'.
# The tests are labelled with the specified 'LABEL' in addition to their
# Catch2 tags, which allows filtering by target/module.
# Other sensible options are added, and are not configurable.
# Note that this command is intended to replace use of 'catch_discover_tests'
# to register tests.
function(aoc_add_tests TARGET LABEL)
  catch_discover_tests(${TARGET}
    EXTRA_ARGS "--warn NoAssertions" "--skip-benchmarks"
    SKIP_IS_FAILURE
    ADD_TAGS_AS_LABELS
    PROPERTIES LABELS "${LABEL}"
  )
endfunction()
