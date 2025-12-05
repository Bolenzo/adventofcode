#ifndef AOC_TRIM_HPP_INCLUDE_GUARD
#define AOC_TRIM_HPP_INCLUDE_GUARD
///////////////////////////////////////////////////////////////////////////////
// File trim.hpp
///////////////////////////////////////////////////////////////////////////////
// This file contains a mechanism, 'aoc::trim_view', that transforms a range
// of strings by trimming leading and trailing whitespaces. The related
// customization point object 'aoc::views::trim' is also available,
// as well as the 'aoc::trim' function used to trim the strings.

#include <ranges> // transform
#include <string_view>

namespace aoc {

// Return a string that is equal to the specified 'str', with every leading
// and trailing whitespace removed; characters that are considered whitespaces
// are the ASCII whitespaces: space (' '), line feed ('\n'), form feed ('\f'),
// carriage return ('\r'), horizontal tab ('\t'), vertical tab ('\v').
// The behaviour is undefined unless 'str' is an ASCII string.
[[nodiscard]] constexpr
auto trim(std::string_view str) -> std::string_view;

namespace views {

inline constexpr auto trim = std::views::transform(aoc::trim);

} // namespace views

} // namespace aoc

///////////////////////////////////////////////////////////////////////////////
// Inline Definitions
///////////////////////////////////////////////////////////////////////////////
#include <cassert>

constexpr
auto aoc::trim(std::string_view str) -> std::string_view {
  // TODO: precondition ASCII string
  constexpr std::string_view ws = " \n\f\r\t\v";
  auto const first = str.find_first_not_of(ws);
  if (first == std::string_view::npos) {
    return {};                                                        // RETURN
  }
  auto const last  = str.find_last_not_of(ws);
  return str.substr(first, last -first + 1);
}

#endif // AOC_TRIM_HPP_INCLUDE_GUARD
