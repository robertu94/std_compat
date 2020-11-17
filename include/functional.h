/**
 * \file
 * \brief back ports of `<functional>`
 */
#ifndef STDCOMPAT_FUNCTIONAL_H
#define STDCOMPAT_FUNCTIONAL_H
#include "std_compat_version.h"
#include <utility>
#include <functional>

namespace compat {
#if !(STDCOMPAT_HAS_MULITPLIES)
/**
 * functor that provides less
 */
template <class T = void>
struct less
{
  /**
   * preforms the evaluation
   * \param u first operand
   * \param v second operand
   */
  template <class U, class V>
  constexpr auto operator()(U&& u, V&& v) const
    noexcept(noexcept(std::forward<U>(u) < std::forward<V>(v)))
      -> decltype(std::forward<U>(u) < std::forward<V>(v))
  {
    return std::forward<U>(u) < std::forward<V>(v);
  }
  using is_transparent = void;
};

/**
 * fuctor that provides multiply
 */
template <class T = void>
struct multiplies
{
  /**
   * preforms the evaluation
   * \param u first operand
   * \param v second operand
   */
  template <class U, class V>
  constexpr auto operator()(U&& u, V&& v) const
    noexcept(noexcept(std::forward<U>(u) * std::forward<V>(v)))
      -> decltype(std::forward<U>(u) * std::forward<V>(v))
  {
    return std::forward<U>(u) * std::forward<V>(v);
  }
  using is_transparent = void;
};
/**
 * fuctor that provides plus
 */
template <class T = void>
struct plus
{
  /**
   * preforms the evaluation
   * \param u first operand
   * \param v second operand
   */
  template <class U, class V>
  constexpr auto operator()(U&& u, V&& v) const
    noexcept(noexcept(std::forward<U>(u) + std::forward<V>(v)))
      -> decltype(std::forward<U>(u) + std::forward<V>(v))
  {
    return u + v;
  }
  using is_transparent = void;
};

/**
 * functor that provides minus
 */
template <class T = void>
struct minus
{
  /**
   * preforms the evaluation
   * \param u first operand
   * \param v second operand
   */
  template <class U, class V>
  constexpr auto operator()(U&& u, V&& v) const
    noexcept(noexcept(std::forward<U>(u) - std::forward<V>(v)))
      -> decltype(std::forward<U>(u) - std::forward<V>(v))
  {
    return u - v;
  }
  using is_transparent = void;
};
#else
using std::multiplies;
using std::plus;
using std::minus;
using std::less;
#endif
}


#endif /* end of include guard: STDCOMPAT_FUNCTIONAL_H */
