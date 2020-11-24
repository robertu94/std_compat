#include "span.h"

#if !STDCOMPAT_HAS_SPAN
namespace compat {
const size_t dynamic_extent = compat_dynamic_extent;
}
#endif
