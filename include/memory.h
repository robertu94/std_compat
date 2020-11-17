/**
 * \file
 * \brief back ports of `<memory>`
 */
#ifndef STDCOMPAT_MEMORY_H
#define STDCOMPAT_MEMORY_H
#include "std_compat_version.h"
#include <memory>
#include "type_traits.h"


namespace compat {
#if (!STDCOMPAT_HAS_MAKE_UNIQUE)
  /**
   * \param args arguments to be forwarded to the constructor
   * \returns a unique_ptr with newly allocated data
   */
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
#else
    using std::make_unique;
#endif


}


#endif /* end of include guard: STDCOMPAT_MEMORY_H */
