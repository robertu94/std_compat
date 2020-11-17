/**
 * \file
 * \brief back ports of `<cstddef>`
 */
#ifndef STDCOMPAT_BYTE_H
#define STDCOMPAT_BYTE_H
#include "std_compat_version.h"
#include <cstddef>

namespace compat {
#if !STDCOMPAT_HAS_BYTE
  /**
   * represents a byte unlike unsigned char does not provide arithmetic operators
   */
  enum class byte : unsigned char {};
#else
  using std::byte;
#endif
}

#endif /* end of include guard: STDCOMPAT_BYTE_H */
