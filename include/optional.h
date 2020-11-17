/**
 * \file
 * \brief back ports of `<optional>`
 */
#ifndef STDCOMPAT_OPTIONAL_H
#define STDCOMPAT_OPTIONAL_H
#include "std_compat_version.h"


#if !(STDCOMPAT_HAS_OPTIONAL)
#include <boost/optional.hpp>
#include <boost/none.hpp>
#else
#include <optional>
#endif

namespace compat {
#if (!STDCOMPAT_HAS_OPTIONAL)
  using boost::optional;
  extern const boost::none_t& nullopt;
#else
  using std::optional;
  using std::nullopt;
#endif
}


#endif /* end of include guard: STDCOMPAT_OPTIONAL_H */
