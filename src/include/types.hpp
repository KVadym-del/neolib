#pragma once

namespace neostd::types
{
using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using size = decltype(sizeof(0));

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

using float32 = float;
using float64 = double;

using byte = unsigned char;

using ptrdiff = decltype(reinterpret_cast<byte *>(0) - reinterpret_cast<byte *>(0));
} // namespace neostd::types
