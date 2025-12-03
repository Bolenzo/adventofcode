#ifndef AOC_CATCH2_HPP_INCLUDE_GUARD
#define AOC_CATCH2_HPP_INCLUDE_GUARD
///////////////////////////////////////////////////////////////////////////////
// File catch2.hpp
///////////////////////////////////////////////////////////////////////////////
// This file is a wrapper around the header file <catch2/catch_all.hpp> that
// contains extensions and customizations of the 'catch2' testing framework
// tailored for the 'aoc' project.
// Any test file of the 'aoc' project that uses 'catch2' should include
// <aoc/unit_test/catch2.hpp> instead of <catch2/catch_all.hpp>.

// The following two warnings are present on Clang when including 'catch2',
// so we suppress them.
// TODO: explore using Clang warning suppression mappings instead.
#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wsign-conversion"
  #pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

#include <catch2/catch_all.hpp>

#if defined(__clang__)
  #pragma clang diagnostic pop
#endif

///////////////////////////////////////////////////////////////////////////////
// Catch::StringMaker specializations
///////////////////////////////////////////////////////////////////////////////

#endif // AOC_CATCH2_HPP_INCLUDE_GUARD
