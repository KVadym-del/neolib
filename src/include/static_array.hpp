#pragma once

#include "types.hpp"
#include "utils.hpp"

#include <initializer_list> // TODO: Replace with initializer_list.hpp
// #include "initializer_list.hpp"

namespace neostd::types
{
template <typename T, types::size S> class static_array
{
  public:
    inline constexpr static_array() = default;
    inline constexpr static_array(const std::initializer_list<T> &init)
    {
        if (init.size() <= S)
            m_lengh = init.size();
        else
            m_lengh = m_size;
        utils::copy(init.begin(), init.end(), m_data);
    }
    inline constexpr explicit static_array(const static_array &other) : m_lengh(other.m_lengh)
    {
        utils::copy(other.m_data, other.m_data + S, m_data);
    }
    inline constexpr explicit static_array(static_array &&other) noexcept : m_lengh(other.m_lengh)
    {
        utils::move(other.m_data, other.m_data + S, m_data);
    }

    inline constexpr ~static_array() = default;

    inline constexpr static_array &operator=(const static_array &other)
    {
        if constexpr (this != &other)
        {
            m_lengh = other.m_lengh;
            utils::copy(other.m_data, other.m_data + S, m_data);
        }
        return *this;
    }
    inline constexpr static_array &operator=(static_array &&other) noexcept
    {
        if constexpr (this != &other)
        {
            m_lengh = other.m_lengh;
            utils::move(other.m_data, other.m_data + S, m_data);
        }
        return *this;
    }
    inline constexpr static_array &operator=(std::initializer_list<T> init)
    {
        m_size = init.size();
        utils::copy(init.begin(), init.end(), m_data);
        return *this;
    }

    inline constexpr T &operator[](types::size index)
    {
        return m_data[index];
    }
    inline constexpr const T &operator[](types::size index) const
    {
        return m_data[index];
    }
    inline constexpr T &at(types::size index)
    {
        return m_data[index];
    }
    inline constexpr const T &at(types::size index) const
    {
        return m_data[index];
    }
    inline constexpr T &front()
    {
        return m_data[0];
    }
    inline constexpr const T &front() const
    {
        return m_data[0];
    }
    inline constexpr T &back()
    {
        return m_data[S - 1];
    }
    inline constexpr const T &back() const
    {
        return m_data[S - 1];
    }
    inline constexpr T *data()
    {
        return m_data;
    }
    inline constexpr const T *data() const
    {
        return m_data;
    }

    inline constexpr bool empty() const noexcept
    {
        return S == 0;
    }
    inline constexpr types::size size() const noexcept
    {
        return m_size;
    }

    inline constexpr types::size lengh() const noexcept
    {
        return m_lengh;
    }

    inline constexpr void fill(const T &value)
    {
        utils::fill(m_data, m_data + S, value);
    }

  private:
    T m_data[S]{};
    const types::size m_size{S};
    types::size m_lengh{};
};
} // namespace neostd::types
