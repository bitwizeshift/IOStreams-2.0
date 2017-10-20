#ifndef IOS2_CONCEPTS_OSTREAM_HPP
#define IOS2_CONCEPTS_OSTREAM_HPP

#include "detail/void_t.hpp" // detail::void_t

#include <type_traits>

namespace ios2 {

  // TODO replace with C++20 version once standardized
#if __cplusplus >= 202000L

  template<typename O, typename CharT>
  concept BasicOStream = requires( O o,
                                   CharT ct,
                                   bool b,
                                   unsigned short us,
                                   signed short ss,
                                   unsigned int ui,
                                   signed int si,
                                   unsigned long ul,
                                   signed long sl,
                                   unsigned long long ull,
                                   signed long long sll,
                                   float f,
                                   double d,
                                   long double ld,
                                   const CharT* s,
                                   const void* p )
  {
    { o.put( ct ) };
    { o.write( s, si ) };
    { o.flush() };
    { o << b } -> O&;
    { o << us } -> O&;
    { o << ss } -> O&;
    { o << ui } -> O&;
    { o << si } -> O&;
    { o << ul } -> O&;
    { o << sl } -> O&;
    { o << ull } -> O&;
    { o << sll } -> O&;
    { o << f } -> O&;
    { o << d } -> O&;
    { o << ld } -> O&;
    { o << p } -> O&;
  };

  template<typename O>
  concept OStream = BasicOStream<O,char>;

  template<typename O>
  concept WOStream = BasicOStream<O,wchar_t>;

#endif

  template<typename T, typename CharT, typename = void>
  struct is_basic_ostream : std::false_type{};

  template<typename T, typename CharT>
  struct is_basic_ostream<T,CharT,
    detail::void_t<
      decltype( std::declval<T&>().put( std::declval<CharT>() ) ),
      decltype( std::declval<T&>().write( std::declval<const CharT*>(), std::declval<std::ptrdiff_t>() )),
      decltype( std::declval<T&>().flush()),
      decltype( std::declval<T&>() << std::declval<unsigned short>() ),
      decltype( std::declval<T&>() << std::declval<signed short>() ),
      decltype( std::declval<T&>() << std::declval<unsigned int>() ),
      decltype( std::declval<T&>() << std::declval<signed int>() ),
      decltype( std::declval<T&>() << std::declval<unsigned long>() ),
      decltype( std::declval<T&>() << std::declval<signed long>() ),
      decltype( std::declval<T&>() << std::declval<unsigned long long>() ),
      decltype( std::declval<T&>() << std::declval<signed long long>() ),
      decltype( std::declval<T&>() << std::declval<float>() ),
      decltype( std::declval<T&>() << std::declval<double>() ),
      decltype( std::declval<T&>() << std::declval<long double>() ),
      decltype( std::declval<T&>() << std::declval<const void*>() )
    >
  > : std::true_type{};

//-----------------------------------------------------------------------------

  template<typename T, typename CharT, typename U, typename = void>
  struct is_basic_ostreamable : std::false_type{};

  template<typename T, typename CharT, typename U>
  struct is_basic_ostreamable<T,CharT,U,
    detail::void_t<
      decltype( std::declval<T&>() << std::declval<U>() )
    >
  > : is_basic_ostream<T,CharT>{};

//-----------------------------------------------------------------------------

  template<typename T>
  using is_ostream = is_basic_ostream<T,char>;

  template<typename T>
  using is_wostream = is_basic_ostream<T,wchar_t>;

  template<typename T, typename U>
  using is_ostreamable = is_basic_ostreamable<T,char,U>;

  template<typename T, typename U>
  using is_wostreamable = is_basic_ostreamable<T,wchar_t,U>;

} // namespace ios2

#endif //IOS2_CONCEPTS_OSTREAM_HPP
