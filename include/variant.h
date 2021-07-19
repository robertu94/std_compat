/**
 * \file
 * \brief back ports of `<variant>`
 */
#ifndef STDCOMPAT_VARIANT_H
#define STDCOMPAT_VARIANT_H
#include "std_compat_version.h"

#if !(STDCOMPAT_HAS_VARIANT)
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size_t.hpp>
#else
#include <variant>
#include <cstddef>
#endif


namespace compat {
#if (!STDCOMPAT_HAS_VARIANT)
  using boost::variant;
  using boost::get;
  struct monostate {};

  bool operator==(monostate const&, monostate const&) noexcept;

  template <typename T, typename... Ts>
  bool holds_alternative(const boost::variant<Ts...>& v) noexcept
  {
      return boost::get<T>(&v) != nullptr;
  }

  template <class... T>
  bool empty(boost::variant<T...> const& v) {
    return v.empty();
  }
  template <class... T>
  size_t index(boost::variant<T...> const& v) {
    return v.which();
  }

  template <size_t N, class Variant>
  struct variant_alternative {
    using type = typename boost::mpl::at<typename Variant::types, typename boost::mpl::size_t<N>>::type;
  };

  template <size_t N, class Variant>
  typename variant_alternative<N,Variant>::type const&
  get(Variant const& v) {
    return boost::get<typename variant_alternative<N,Variant>::type>(v);
  }

  template <size_t N, class Variant>
  typename variant_alternative<N,Variant>::type&
  get(Variant& v) {
    return boost::get<typename variant_alternative<N,Variant>::type>(v);
  }

  extern size_t const variant_npos;
#else
  using std::variant;
  using std::monostate;
  using std::holds_alternative;
  using std::get;
  using std::variant_npos;
  using std::variant_alternative;

  template <class... T>
  bool empty(std::variant<T...> const& v) {
    return v.index() == std::variant_npos;
  }
  template <class... T>
  size_t index(std::variant<T...> const& v) {
    return v.index();
  }
#endif

}

#endif /* end of include guard: STDCOMPAT_VARIANT_H */
