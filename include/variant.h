/**
 * \file
 * \brief back ports of `<variant>`
 */
#ifndef STDCOMPAT_VARIANT_H
#define STDCOMPAT_VARIANT_H
#include "std_compat_version.h"

#if !(STDCOMPAT_HAS_VARIANT)
#include <boost/variant.hpp>
#else
#include <variant>
#endif


namespace compat {
#if (!STDCOMPAT_HAS_VARIANT)
  using boost::variant;
  using boost::get;
  struct monostate {};
  template <typename T, typename... Ts>
  bool holds_alternative(const boost::variant<Ts...>& v) noexcept
  {
      return boost::get<T>(&v) != nullptr;
  }
#else
  using std::variant;
  using std::monostate;
  using std::holds_alternative;
  using std::get;
#endif

}

#endif /* end of include guard: STDCOMPAT_VARIANT_H */
