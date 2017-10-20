#ifndef IOS2_CONCEPTS_DETAIL_VOID_T_HPP
#define IOS2_CONCEPTS_DETAIL_VOID_T_HPP

namespace ios2 {
  namespace detail {
    template<typename...Types>
    struct voidify{ using type = void; };

    template<typename...Types>
    using void_t = typename voidify<Types...>::type;
  } // namespace detail
} // namespace ios2

#endif //IOS2_CONCEPTS_DETAIL_VOID_T_HPP
