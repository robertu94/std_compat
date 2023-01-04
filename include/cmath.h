#ifndef STDCOMPAT_CMATH_H
#define STDCOMPAT_CMATH_H

#include <cmath>

namespace compat {
#if !(STDCOMPAT_HAS_LERP)

namespace detail {

template <class Tp> struct numeric_type {
  static void test(...);
  static float test(float);
  static double test(char);
  static double test(int);
  static double test(unsigned);
  static double test(long);
  static double test(unsigned long);
  static double test(long long);
  static double test(unsigned long long);
  static double test(double);
  static long double test(long double);

  typedef decltype(test(std::declval<Tp>())) type;
  static const bool value = !std::is_same<type, void>::value;
};

template <> struct numeric_type<void> {
  static const bool value = true;
};

template <class A1, class A2 = void, class A3 = void,
          bool = numeric_type<A1>::value &&numeric_type<A2>::value
              &&numeric_type<A3>::value>
class promote_impl {
public:
  static const bool value = false;
};

template <class A1, class A2, class A3>
class promote_impl<A1, A2, A3, true> {
private:
  typedef typename promote_impl<A1>::type type1;
  typedef typename promote_impl<A2>::type type2;
  typedef typename promote_impl<A3>::type type3;

public:
  typedef decltype(type1() + type2() + type3()) type;
  static const bool value = true;
};

template <class A1, class A2> class promote_impl<A1, A2, void, true> {
private:
  typedef typename promote_impl<A1>::type type1;
  typedef typename promote_impl<A2>::type type2;

public:
  typedef decltype(type1() + type2()) type;
  static const bool value = true;
};

template <class A1> class promote_impl<A1, void, void, true> {
public:
  typedef typename numeric_type<A1>::type type;
  static const bool value = true;
};

template <class A1, class A2 = void, class A3 = void>
class promote : public promote_impl<A1, A2, A3> {};


template <typename Fp>
constexpr Fp lerp(Fp a, Fp b, Fp t) noexcept {
  if ((a <= 0 && b >= 0) || (a >= 0 && b <= 0))
    return t * b + (1 - t) * a;

  if (t == 1)
    return b;
  const Fp x = a + t * (b - a);
  if ((t > 1) == (b > a))
    return b < x ? x : b;
  else
    return x < b ? x : b;
}
} // namespace detail


constexpr float lerp(float a, float b, float t) noexcept {
return detail::lerp(a, b, t);
}

constexpr double lerp(double a, double b, double t) noexcept {
return detail::lerp(a, b, t);
}

constexpr long double lerp(long double a, long double b,
                           long double t) noexcept {
return detail::lerp(a, b, t);
}

template <class A1, class A2, class A3>
inline constexpr typename std::enable_if_t<std::is_arithmetic<A1>::value &&
                                               std::is_arithmetic<A2>::value &&
                                               std::is_arithmetic<A3>::value,
                                           detail::promote<A1, A2, A3>>::type
lerp(A1 a, A2 b, A3 t) noexcept {
  typedef typename detail::promote<A1, A2, A3>::type result_type;
  static_assert(!(std::is_same<A1, result_type>::value &&
                  std::is_same<A2, result_type>::value &&
                  std::is_same<A3, result_type>::value));
  return detail::lerp((result_type)a, (result_type)b, (result_type)t);
}

#else
using std::lerp;
#endif
} // namespace compat

#endif /* end of include guard: STDCOMPAT_CMATH_H */
