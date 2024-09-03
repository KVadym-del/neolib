#pragma once

#include "types.hpp"

namespace neostd::utils
{
template <class InputIt, class OutputIt> inline constexpr OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

template <typename T> struct strip_reference
{
    using type = T;
};
template <typename T> struct strip_reference<T &>
{
    using type = T;
};
template <typename T> struct strip_reference<T &&>
{
    using type = T;
};
template <class T> inline constexpr utils::strip_reference<T> &&move(T &&t) noexcept
{
    return static_cast<utils::strip_reference<T> &&>(t);
}

template <typename ForwardIterator, typename T>
inline constexpr void fill(ForwardIterator first, ForwardIterator last, const T &value)
{
    while (first != last)
    {
        *first = value;
        ++first;
    }
}
} // namespace neostd::utils
