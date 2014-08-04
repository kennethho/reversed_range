/*
  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  Version 2, December 2004

  Copyright (C) 2014 Kenneth Ho <ken@fsfoundry.org>

  Everyone is permitted to copy and distribute verbatim or modified
  copies of this license document, and changing it is allowed as long
  as the name is changed.

  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#ifndef REVERSED_RANGE_HPP
#define REVERSED_RANGE_HPP

#include <iterator>
#include <utility>

namespace reversed_range
{

namespace detail
{
  // Proxy functions to begin/end overloads those are found
  // 1. though ADL, or
  // 2. in namespace std

  using std::begin;
  using std::end;

  template <class Range>
  auto begin_(Range const &rng) -> decltype(begin(rng))
  {
    return begin(rng);
  }
  template <class Range>
  auto begin_(Range &rng) -> decltype(begin(rng))
  {
    return begin(rng);
  }
  template <class Range>
  auto end_(Range const &rng) -> decltype(end(rng))
  {
    return end(rng);
  }
  template <class Range>
  auto end_(Range &rng) -> decltype(end(rng))
  {
    return end(rng);
  }

  template <class Range>
  auto cbegin_(Range const &rng) -> decltype(begin(rng))
  {
    return begin(rng);
  }
  template <class Range>
  auto cend_(Range const &rng) -> decltype(end(rng))
  {
    return end(rng);
  }
} // namespace detail

template <class Iterator>
auto make_reverse_iterator(Iterator i)
  -> decltype(std::reverse_iterator<Iterator>(i))
{
  return std::reverse_iterator<Iterator>(i);
}

template <class Range>
auto rbegin(Range const &rng)
  -> decltype(make_reverse_iterator(detail::end_(rng)))
{
  return make_reverse_iterator(detail::end_(rng));
}
template <class Range>
auto rbegin(Range &rng)
  -> decltype(make_reverse_iterator(detail::end_(rng)))
{
  return make_reverse_iterator(detail::end_(rng));
}
template <class Range>
auto rend(Range const &rng)
  -> decltype(make_reverse_iterator(detail::begin_(rng)))
{
  return make_reverse_iterator(detail::begin_(rng));
}
template <class Range>
auto rend(Range &rng)
  -> decltype(make_reverse_iterator(detail::begin_(rng)))
{
  return make_reverse_iterator(detail::begin_(rng));
}

template <class Range>
auto crbegin(Range const &rng)
  -> decltype(rbegin(rng))
{
  return rbegin(rng);
}
template <class Range>
auto crend(Range const &rng)
  -> decltype(rend(rng))
{
  return rend(rng);
}

template <class Range>
class reversed_range_adopter
{
public:
  using range_type = Range;
  using range_iterator = decltype(detail::begin_(std::declval<range_type&>()));
  using iterator = std::reverse_iterator<range_iterator>;

  explicit reversed_range_adopter(Range& rng)
    : b_(detail::begin_(rng)),
      e_(detail::end_(rng))
  {
  }

  iterator begin() const noexcept
  {
    return std::reverse_iterator<range_iterator>(e_);
  }
  iterator end() const noexcept
  {
    return std::reverse_iterator<range_iterator>(b_);
  }

private:
  range_iterator b_;
  range_iterator e_;
};

template <class Range>
auto reversed(Range const &rng)
  ->reversed_range_adopter<const Range>
{
  return reversed_range_adopter<Range const>(rng);
}

template <class Range>
auto reversed(Range &rng)
  ->reversed_range_adopter<Range>
{
  return reversed_range_adopter<Range>(rng);
}

template <class Range>
auto creversed(Range const &rng)
  -> decltype(reversed(rng))
{
  return reversed(rng);
}

} // namespace reversed_range

#endif // #ifndef REVERSED_RANGE_HPP
