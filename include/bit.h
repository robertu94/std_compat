#include "std_compat_version.h"

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
}
