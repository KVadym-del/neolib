#pragma once

#include "types.hpp"

namespace neostd::types
{
class string
{
  public:
    string() = default;
    string(const char *str);
    string(const string &other);
    string(string &&other) noexcept;
    ~string();

    string &operator=(const string &other);
    string &operator=(string &&other) noexcept;

    const char *c_str() const;
    types::size size() const;

    bool operator==(const string &other) const;
    bool operator!=(const string &other) const;

    bool operator<(const string &other) const;
    bool operator>(const string &other) const;
    bool operator<=(const string &other) const;
    bool operator>=(const string &other) const;

    string operator+(const string &other) const;
    string &operator+=(const string &other);

    char operator[](types::size index) const;

  private:
    char *m_data = nullptr;
    types::size m_size = 0;
    types::size m_capacity = 0;
};
} // namespace neostd::types

namespace neostd::types::string_tools
{
types::size string_length(const char *str);
void string_copy(char *dest, const char *src);
bool string_compare(const char *str1, const char *str2);
char *string_concat(char *dest, const char *src);
} // namespace neostd::types::string_tools
