#ifndef STDCOMPAT_MUTEX_H
#define STDCOMPAT_MUTEX_H

//these features were added together, so we can just test for the shared version
#if !(STDCOMPAT_HAS_SHARED_MUTEX)
#include <boost/thread/locks.hpp>
#else
#include <mutex>
#endif

#include "std_compat_version.h"

namespace compat {
#if !(STDCOMPAT_HAS_SHARED_MUTEX)
  using boost::unique_lock;
#else
  using std::unique_lock;
#endif
}

#endif
