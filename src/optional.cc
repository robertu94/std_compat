#include "optional.h"

#if !(STDCOMPAT_HAS_OPTIONAL)
const boost::none_t& nullopt = boost::none;
#endif
