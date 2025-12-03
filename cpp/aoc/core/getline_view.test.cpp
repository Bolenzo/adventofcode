///////////////////////////////////////////////////////////////////////////////
// File getline_view.test.cpp
///////////////////////////////////////////////////////////////////////////////
#include <aoc/core/getline_view.hpp>
#include <aoc/unit_test/catch2.hpp>

#include <sstream> // istringstream

TEST_CASE("'aoc::views::getline' with empty stream", "[getline_view]")
{
  auto const delim = GENERATE('\n', ' ', 'x');
  std::istringstream stream;
  auto lines = aoc::views::getline(stream, delim);
  REQUIRE(lines.begin() == lines.end());
}

TEST_CASE("'aoc::views::getline' with non-empty stream", "[getline_view]")
{
  std::istringstream stream{"Line1\nLine2\n"};
  auto lines = aoc::views::getline(stream);
  auto it =  lines.begin();
  REQUIRE(it != lines.end());
  REQUIRE(*it == "Line1");
  ++it;
  REQUIRE(it != lines.end());
  REQUIRE(*it == "Line2");
  ++it;
  REQUIRE(it == lines.end());
}

TEST_CASE("'aoc::views::getline' to vector", "[getline_view]")
{
  std::istringstream stream{"Line1\nLine2\nLine3"};
  auto const lines = aoc::views::getline(stream)
                   | std::ranges::to<std::vector>();
  REQUIRE_THAT(lines, Catch::Matchers::Equals(
               std::vector<std::string>{"Line1", "Line2", "Line3"}));
}

TEST_CASE("'aoc::views::getline' with custom delimiter", "[getline_view]")
{
  std::istringstream stream{"abcdefu"};
  auto const lines = aoc::views::getline(stream, 'e')
                   | std::ranges::to<std::vector>();
  REQUIRE_THAT(lines, Catch::Matchers::Equals(
               std::vector<std::string>{"abcd", "fu"}));
}
