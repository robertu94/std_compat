#ifndef STDCOMPAT_SHARED_MUTEX_H
#define STDCOMPAT_SHARED_MUTEX_H
#include "std_compat_version.h"

#if !(STDCOMPAT_HAS_SHARED_MUTEX)
#include <boost/thread/shared_mutex.hpp>
#else
#include <shared_mutex>
#endif


namespace compat {
#if !(STDCOMPAT_HAS_SHARED_MUTEX)
  using boost::shared_mutex;
  using boost::shared_lock;
#else
  using std::shared_mutex;
  using std::shared_lock;
#endif
}

#endif
