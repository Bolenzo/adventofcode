#ifndef AOC_GETLINE_VIEW_HPP_INCLUDE_GUARD
#define AOC_GETLINE_VIEW_HPP_INCLUDE_GUARD
///////////////////////////////////////////////////////////////////////////////
// File getline_view.hpp
///////////////////////////////////////////////////////////////////////////////
// This file contains a mechanism, 'aoc::getline_view', that generates a
// sequence of strings by repeatedly calling 'std::getline'. The related
// customization point object 'aoc::views::getline' is also available.

#include <istream>
#include <string>
#include <iterator> // input_iterator_tag, default_sentinel_t
#include <cstddef>  // ptrdiff_t

namespace aoc {

/******************************************************************************
* Class aoc::getline_view
******************************************************************************/
// This mechanism is a range factory that generates a sequence of strings by
// repeatedly calling 'std::getline'.
class getline_view
{
  std::istream* m_stream_ptr;
  std::string m_line_buffer; // TODO: add pmr allocator
  char m_delim;

public:
  // Create a 'getline_view' factory that generates strings from the specified
  // 'stream', by invoking 'std::getline' using the default delimiter.
  [[nodiscard]]
  getline_view(std::istream& stream) noexcept;

  // Create a 'getline_view' factory that generates strings from the specified
  // 'stream', by invoking 'std::getline' with the specified 'delimiter'.
  [[nodiscard]]
  getline_view(std::istream& stream, char delimiter) noexcept;

  // The iterator type of this range.
  class iterator;
  // Return an iterator to the first string created by this range by invoking
  // 'std::getline', or an iterator that compares equal to 'this->end()' if
  // no line canbe extracted from the underlying range.
  [[nodiscard]]
  auto begin() -> iterator;
  // Return a sentinel that denotes the end of this range.
  [[nodiscard]]
  auto end() const noexcept -> std::default_sentinel_t;

private:
  // Extract a line from the underlying stream of this range factory using
  // 'std::getline', and store the result in its line buffer.
  void m_getline();
};

namespace views {

namespace detail {

struct getline_fn
{
  // Return 'aoc::getline_view{stream}'.
  [[nodiscard]]
  auto operator()(std::istream& stream) const noexcept -> getline_view;

  // Return 'aoc::getline_view{stream, delim}'.
  [[nodiscard]]
  auto operator()(std::istream& stream, char delim) const noexcept
                                                               -> getline_view;
};

} // namespace detail

/******************************************************************************
* Class aoc::views::getline
******************************************************************************/
// This customization point object for the factory 'aoc::getline_views' is
// such that 'aoc::views::getline(stream, delim)' is expression-equivalent to
// 'aoc::getline_view{stream, delim}', and 'aoc::views::getline(stream)' is
// expression-equivalent to 'aoc::getline_view{stream}'.
inline constexpr detail::getline_fn getline;

} // namespace views

/******************************************************************************
* Class aoc::getline_view::iterator
******************************************************************************/
// This class defines an input iterator for the 'aoc::getline_view' factory.
class getline_view::iterator
{
  getline_view* m_parent;

public:
  using iterator_concept = std::input_iterator_tag;
  using value_type        = std::string;
  using reference         = value_type&;
  using pointer           = value_type*;
  using difference_type   = std::ptrdiff_t;

  // Return the line at which this iterator is positioned.
  // The behaviour is undefined unless this iterator is dereferenceable.
  [[nodiscard]]
  auto operator*() const -> reference;

  // Advance this iterator by one position by invoking 'std::getline', and
  // return a reference providing modifiable access to this iterator.
  // The behaviour is undefined unless this iterator is dereferenceable.
  auto operator++() -> iterator&;

  // Advance this iterator by one position.
  // Note that this is equivalent to '(void)++*this'.
  // The behaviour is undefined unless this iterator is dereferenceable.
  void operator++(int);

  // Return 'true' if this iterator is positioned at the end of the range it
  // iterates, and 'false' otherwise.
  [[nodiscard]]
  bool operator==(std::default_sentinel_t) const noexcept;

private:
  friend getline_view; // allow initializing an iterator
};

} // namespace aoc

///////////////////////////////////////////////////////////////////////////////
// Inline Definitions
///////////////////////////////////////////////////////////////////////////////
#include <cassert>

inline
aoc::getline_view::getline_view(std::istream& stream) noexcept
: getline_view{stream, stream.widen('\n')}
{ }

///////////////////////////////////////////////////////////////////////////////

inline
aoc::getline_view::getline_view(std::istream& stream,
                                char const delimiter) noexcept
: m_stream_ptr{&stream}
, m_delim{delimiter}
{ }

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::getline_view::begin() -> iterator {
  this->m_getline();
  iterator it;
  it.m_parent = &*this;
  return it;
}

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::getline_view::end() const noexcept -> std::default_sentinel_t {
  return {};
}

///////////////////////////////////////////////////////////////////////////////

inline
void aoc::getline_view::m_getline() {
  std::getline(*m_stream_ptr, m_line_buffer, m_delim);
}

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::views::detail::getline_fn::operator()(
                         std::istream& stream) const noexcept -> getline_view {
  return aoc::getline_view{stream};
}

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::views::detail::getline_fn::operator()(
       std::istream& stream, char const delim) const noexcept -> getline_view {
  return aoc::getline_view{stream, delim};
}

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::getline_view::iterator::operator*() const -> reference {
  assert(*this != std::default_sentinel);
  return m_parent->m_line_buffer;
}

///////////////////////////////////////////////////////////////////////////////

inline
auto aoc::getline_view::iterator::operator++() -> iterator& {
  assert(*this != std::default_sentinel);
  m_parent->m_getline();
  return *this;
}

///////////////////////////////////////////////////////////////////////////////

inline
void aoc::getline_view::iterator::operator++(int) {
  ++*this;
}

///////////////////////////////////////////////////////////////////////////////

inline
bool aoc::getline_view::iterator::operator==(
                                      std::default_sentinel_t) const noexcept {
  return m_parent->m_stream_ptr->fail();
}

#endif // AOC_GETLINE_VIEW_HPP_INCLUDE_GUARD
