/**
 * \file
 * \brief macros which conditionally enable some C++ language improvements
 */
#include <utility>

#if __cplusplus >= 201703L
#define  RVO_MOVE(x) (x)
#define  DEFAULTED_NOEXCEPT noexcept
#define  STDCOMPAT_CONSTEXPR constexpr
#define  STDCOMPAT_CONSTEXPR_CONSTRUCTOR constexpr
#else
#define  RVO_MOVE(x) std::move(x)
#define  DEFAULTED_NOEXCEPT
#define  STDCOMPAT_CONSTEXPR
#define  STDCOMPAT_CONSTEXPR_CONSTRUCTOR
#endif
