#pragma once

#include "types.hpp"

namespace neostd::utils
{

template <class T> class initializer_list
{
  public:
    constexpr inline initializer_list() noexcept : m_begin(nullptr), m_size(0)
    {
    }

    constexpr inline initializer_list(const T *first, types::size count) noexcept : m_begin(first), m_size(count)
    {
    }

    constexpr inline const T *begin() const noexcept
    {
        return m_begin;
    }
    constexpr inline const T *end() const noexcept
    {
        return m_begin + m_size;
    }

    constexpr inline types::size size() const noexcept
    {
        return m_begin;
    }

  private:
    const T *m_begin;
    types::size m_size;
};

template <typename T> constexpr const T *begin(initializer_list<T> il) noexcept
{
    return il.begin();
}

template <typename T> constexpr const T *end(initializer_list<T> il) noexcept
{
    return il.end();
}
} // namespace neostd::utils
