/**
 * \file
 * \brief back ports of `<optional>`
 */
#ifndef STDCOMPAT_STRING_VIEW_H
#define STDCOMPAT_STRING_VIEW_H
#include "std_compat_version.h"


#if !(STDCOMPAT_HAS_STRING_VIEW)
#include <boost/utility/string_view.hpp>
#else
#include <string_view>
#endif

namespace compat {
#if (!STDCOMPAT_HAS_STRING_VIEW)
  using boost::string_view;
#else
#include<string_view>
  using std::string_view;
#endif
}


#endif /* end of include guard: STDCOMPAT_STRING_VIEW_H */
