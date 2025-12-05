///////////////////////////////////////////////////////////////////////////////
// File trim.test.cpp
///////////////////////////////////////////////////////////////////////////////
#include <aoc/core/trim.hpp>
#include <aoc/unit_test/catch2.hpp>

#include <vector>

TEST_CASE("'aoc::trim'", "[trim]")
{
  STATIC_REQUIRE(aoc::trim("") == "");
  STATIC_REQUIRE(aoc::trim("abc") == "abc");
  STATIC_REQUIRE(aoc::trim(   "C"  ) == "C");
  STATIC_REQUIRE(aoc::trim(" \f \n foo") == "foo");
  STATIC_REQUIRE(aoc::trim("bar\t\v") == "bar");
  STATIC_REQUIRE(aoc::trim(" \rfoo bar\n\r") == "foo bar");
}

TEST_CASE("'aoc::views::trim'", "[trim]")
{
  auto const r = std::vector{" Hello\n", "\t\tAOC", " \v World!\n\n"};
  auto const trimmed = r | aoc::views::trim | std::ranges::to<std::vector>();
  REQUIRE_THAT(trimmed, Catch::Matchers::Equals(
               std::vector<std::string_view>{"Hello", "AOC", "World!"}));
}
