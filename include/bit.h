#include "std_compat_version.h"
#include <cstdint>

namespace compat {
#if !(STDCOMPAT_HAS_ENDIAN)
enum class endian
{
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little
#else
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#endif
};
#else
#include <bit>
using std::endian;
#endif

#if !(STDCOMPAT_HAS_BYTESWAP)
  /*
   * Adapted from the Microsoft STL licensed under the Apache 2.0 license with LLVM exception
   * See https://github.com/microsoft/STL/blob/main/LICENSE.txt for a copy of the license
   *
   * Changed to be more compatible with C++11 and remove dependence on compiler intrinsics
   */
  namespace impl {
    constexpr uint16_t swap16(uint16_t n) {
      return static_cast<uint16_t>((n << 8) | (n >> 8));
    }
    constexpr uint32_t swap32(uint32_t n) {
      return (n << 24) | ((n << 8) & 0x00FF0000) | ((n >> 8) & 0x0000FF00) | (n >> 24);
    }
    constexpr uint64_t swap64(uint64_t n) {
      return (n << 56) | ((n << 40) & 0x00FF000000000000) | ((n << 24) & 0x0000FF0000000000)
             | ((n << 8) & 0x000000FF00000000) | ((n >> 8) & 0x00000000FF000000)
             | ((n >> 24) & 0x0000000000FF0000) | ((n >> 40) & 0x000000000000FF00) | (n >> 56);
    }
  }
  template <class T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
  constexpr T byteswap(T n) noexcept {
    static_assert(sizeof(T) <= 8, "supports only up to uint64_t");
    return (sizeof(T) == 1)? n:
      (sizeof(T) == 2) ?  static_cast<T>(impl::swap16(static_cast<uint16_t>(n))) :
      (sizeof(T) == 4) ?  static_cast<T>(impl::swap32(static_cast<uint32_t>(n))) :
      static_cast<T>(impl::swap64(static_cast<uint64_t>(n)));
  }
#else
#include <bit>
 using std::byteswap;
#endif
}
