#ifndef AOC_INPUT_HPP_INCLUDE_GUARD
#define AOC_INPUT_HPP_INCLUDE_GUARD
///////////////////////////////////////////////////////////////////////////////
// File input.hpp
///////////////////////////////////////////////////////////////////////////////
// This file contains a suite of range adapters that are commonly used to
// parse the input of a problem.

#include <functional> // mem_fn, not_fn
#include <ranges> // drop_while, take_while
#include <string>
#include <aoc/core/trim.hpp>

namespace aoc {

namespace views {

/******************************************************************************
* Class aoc::views::line_block
******************************************************************************/
// This customization point object is a range adapter that trims a range of
// strings using 'aoc::views::trim', and returns the first block of nonempty
// (originally non-blank) lines.
inline constexpr auto line_block
  = aoc::views::trim
  | std::views::drop_while(std::mem_fn(&std::string_view::empty))
  | std::views::take_while(std::not_fn(std::mem_fn(&std::string_view::empty)));

/******************************************************************************
* Class aoc::views::line_blocks
******************************************************************************/
// This customization point object is a range adapter that trims a range of
// strings using 'aoc::views::trim', and returns a range of up to the specified
// 'n' blocks of nonempty (originally non-blank) lines.
// TODO

} // namespace views

/******************************************************************************
* Class aoc::to_strings
******************************************************************************/
// This customization point object is an alias for the range adapter
// 'std::ranges::to<std::vector<std::string>>', that is commonly used.
inline constexpr auto to_strings = std::ranges::to<std::vector<std::string>>;

} // namespace aoc

#endif // AOC_INPUT_HPP_INCLUDE_GUARD
