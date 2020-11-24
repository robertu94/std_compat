#include "variant.h"
#include <limits>
#include <cstddef>

#if !(STDCOMPAT_HAS_VARIANT)
namespace compat {
const size_t variant_npos = std::numeric_limits<size_t>::max();
}
#endif
