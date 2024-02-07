/**
 * \file
 * \brief back ports of `<algorithm>`
 */
#ifndef STDCOMPAT_ALGORITHM_H
#define STDCOMPAT_ALGORITHM_H
#include "std_compat_version.h"
#include "language.h"
#include <algorithm>
#include <cassert>

namespace compat {
#if !(STDCOMPAT_HAS_NTH_ELEMENT)
  /**
   * Finds the kth order element
   * \param first random access iterator to the first element
   * \param nth random access iterator pointing to the position of the kth order element after the nth_element finishes
   * \param last random access iterator to the end of the container
   */
  template <class RandomIt>
  void nth_element(RandomIt first, RandomIt nth, RandomIt last) {
    (void)nth;
    std::sort(first, last);
  }

  /**
   * Finds the kth order element
   * \param first random access iterator to the first element
   * \param nth random access iterator pointing to the position of the kth order element after the nth_element finishes
   * \param last random access iterator to the end of the container
   * \param compare the comparator to use while comparing
   */
  template <class RandomIt, class Compare>
  void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare compare) {
    (void)nth;
    std::sort(first, last, compare);
  }
#else
  using std::nth_element;
#endif

#if !(STDCOMPAT_HAS_CLAMP)
  /**
   * clamps a value between low and high
   * \param v the value to clamp
   * \param low the low end to clamp to
   * \param hi the high end to clamp to
   */
template<class T>
constexpr const T& clamp( const T& v, const T& low, const T& hi )
{
#if __cplusplus >= 201703L
    assert( !(hi < low) );
#endif
    return (v < low) ? low : (hi < v) ? hi : v;
}

  /**
   * clamps a value between low and high
   * \param v the value to clamp
   * \param low the low end to clamp to
   * \param high the high end to clamp to
   * \param comp the comparator to use for comparisons
   */
template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& low, const T& high, Compare comp )
{
#if __cplusplus >= 201703L
    assert( !comp(high, low) );
#endif
    return comp(v, low) ? low : comp(high, v) ? high : v;
}
#else
  using std::clamp;
#endif

#if !(STDCOMPAT_HAS_FOUR_ITER_EQUALS)
template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1,
           InputIt2 first2, InputIt2 last2)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (not (*first1 == *first2)) {
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}
  
template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1,
           InputIt2 first2, InputIt2 last2, BinaryPredicate p)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (not p(*first1, *first2)) {
            return false;
        }
    }
    return first1 == last1 && first2 == last2;
}
#else
  using std::equals;
#endif

}

#endif /* end of include guard: STDCOMPAT_ALGORITHM_H */
