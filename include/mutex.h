#ifndef STDCOMPAT_MUTEX_H
#define STDCOMPAT_MUTEX_H

#include "std_compat_version.h"

//these features were added together, so we can just test for the shared version
#if !(STDCOMPAT_HAS_MUTEX)
#include <boost/thread/locks.hpp>
#else
#include <mutex>
#endif


namespace compat {
#if !(STDCOMPAT_HAS_MUTEX)
  using boost::unique_lock;
  using boost::lock_guard;
  using boost::mutex;
#else
  using std::unique_lock;
  using std::lock_guard;
  using std::mutex;
#endif
}

#endif
