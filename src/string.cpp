#include "string.hpp"

#include "memory.hpp"

namespace neostd::types
{
string::string(const char *str)
{
    if (str)
    {
        if (str)
        {
            m_size = string_tools::string_length(str);
            if (m_size >= m_preallocated_size)
            {
                m_capacity = m_size + 1;
                m_dynamic_data = new char[m_capacity];
                string_tools::string_copy(m_dynamic_data, str);
            }
            else
            {
                m_capacity = m_preallocated_size;
                string_tools::string_copy(m_static_data, str);
            }
        }
    }
}
string::string(const string &other)
{
    m_size = other.m_size;
    if (m_size >= m_preallocated_size)
    {
        m_capacity = other.m_capacity;
        m_dynamic_data = new char[m_capacity];
        string_tools::string_copy(m_dynamic_data, other.m_dynamic_data);
    }
    else
    {
        m_capacity = m_preallocated_size;
        string_tools::string_copy(m_static_data, other.m_static_data);
    }
}
string::string(string &&other) noexcept
{
    if (other.m_size >= m_preallocated_size)
    {
        m_dynamic_data = other.m_dynamic_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_dynamic_data = nullptr;
    }
    else
    {
        string_tools::string_copy(m_static_data, other.m_static_data);
        m_size = other.m_size;
        m_capacity = m_preallocated_size;
    }
    other.m_size = 0;
}
string::~string()
{
    if (m_size >= m_preallocated_size)
    {
        delete[] m_dynamic_data;
    }
}

string &string::operator=(const string &other)
{
    if (this != &other)
    {
        if (m_size >= m_preallocated_size)
        {
            delete[] m_dynamic_data;
        }

        m_size = other.m_size;
        if (m_size >= m_preallocated_size)
        {
            m_capacity = other.m_capacity;
            m_dynamic_data = new char[m_capacity];
            string_tools::string_copy(m_dynamic_data, other.m_dynamic_data);
        }
        else
        {
            m_capacity = m_preallocated_size;
            string_tools::string_copy(m_static_data, other.m_static_data);
        }
    }
    return *this;
}

string &string::operator=(string &&other) noexcept
{
    if (this != &other)
    {
        if (m_size >= m_preallocated_size)
        {
            delete[] m_dynamic_data;
        }

        if (other.m_size >= m_preallocated_size)
        {
            m_dynamic_data = other.m_dynamic_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_dynamic_data = nullptr;
        }
        else
        {
            string_tools::string_copy(m_static_data, other.m_static_data);
            m_size = other.m_size;
            m_capacity = m_preallocated_size;
        }
        other.m_size = 0;
    }
    return *this;
}

const char *string::c_str() const
{
    return (m_size >= m_preallocated_size) ? m_dynamic_data : m_static_data;
}

types::size string::size() const
{
    return m_size;
}

bool string::operator==(const string &other) const
{
    return string_tools::string_compare(c_str(), other.c_str());
}

bool string::operator!=(const string &other) const
{
    return !(*this == other);
}

bool string::operator<(const string &other) const
{
    return string_tools::string_length(c_str()) < string_tools::string_length(other.c_str());
}

bool string::operator>(const string &other) const
{
    return string_tools::string_length(c_str()) > string_tools::string_length(other.c_str());
}

bool string::operator<=(const string &other) const
{
    return !(*this > other);
}

bool string::operator>=(const string &other) const
{
    return !(*this < other);
}

string string::operator+(const string &other) const
{
    string result;
    result.m_size = m_size + other.m_size;
    if (result.m_size >= m_preallocated_size)
    {
        result.m_capacity = result.m_size + 1;
        result.m_dynamic_data = new char[result.m_capacity];
        string_tools::string_copy(result.m_dynamic_data, c_str());
        string_tools::string_concat(result.m_dynamic_data, other.c_str());
    }
    else
    {
        result.m_capacity = m_preallocated_size;
        string_tools::string_copy(result.m_static_data, c_str());
        string_tools::string_concat(result.m_static_data, other.c_str());
    }
    return result;
}

string &string::operator+=(const string &other)
{
    *this = *this + other;
    return *this;
}

char string::operator[](types::size index) const
{
    if (index >= m_size)
    {
        return '\0';
    }
    return (m_size >= m_preallocated_size) ? m_dynamic_data[index] : m_static_data[index];
}
} // namespace neostd::types

namespace neostd::types::string_tools
{
types::size string_length(const char *start)
{
    const char *end = start;
    while (*end != '\0')
        ++end;
    return end - start;
}

void string_copy(char *dest, const char *src)
{
    while (*src != '\0')
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
}

bool string_compare(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
            return false;
        ++str1;
        ++str2;
    }
    return *str1 == *str2;
}

char *string_concat(char *dest, const char *src)
{
    char *start = dest;
    while (*dest != '\0')
        ++dest;
    while (*src != '\0')
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
    return start;
}
} // namespace neostd::types::string_tools
