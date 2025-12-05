///////////////////////////////////////////////////////////////////////////////
// File input.test.cpp
///////////////////////////////////////////////////////////////////////////////
#include <aoc/core/input.hpp>
#include <aoc/unit_test/catch2.hpp>

#include <array>
#include <list>
#include <vector>
#include <aoc/core/getline_view.hpp>

TEST_CASE("'aoc::to_strings'", "[input]") {
  SECTION("Empty range") {
    auto const r = std::list<std::string_view>{};
    REQUIRE((r | aoc::to_strings()).empty());
  }
  SECTION("Non-empty range") {
    auto const r = std::array<std::string_view, 3>{"AOC", "is", "great!"};
    REQUIRE_THAT(r | aoc::to_strings(), Catch::Matchers::Equals(
               std::vector<std::string>{"AOC", "is", "great!"}));
  }
}

TEST_CASE("'aoc::views::line_block'", "[input]")
{
  auto const r = std::vector{"", " This is\n", " the first block.\n",
                             "", "here comes the 2nd"};
  auto block = r | aoc::views::line_block;
  REQUIRE_THAT(block | aoc::to_strings(), Catch::Matchers::Equals(
               std::vector<std::string>{"This is", "the first block."}));
}

TEST_CASE("'aoc::views::line_block' with 'aoc::views::getline'", "[input]")
{
  std::istringstream stream{"\n    \nQWE\nASD\nZXC\n"};
  auto block = aoc::views::getline(stream) | aoc::views::line_block;
  REQUIRE_THAT(block | aoc::to_strings(), Catch::Matchers::Equals(
               std::vector<std::string>{"QWE", "ASD", "ZXC"}));
}
