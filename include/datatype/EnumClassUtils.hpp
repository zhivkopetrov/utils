#ifndef UTILS_INCLUDE_DATATYPE_ENUMCLASSUTILS_HPP_
#define UTILS_INCLUDE_DATATYPE_ENUMCLASSUTILS_HPP_

// C system headers

// C++ system headers
#include <type_traits>

// Other libraries headers

// Own components headers

/* extract value from enumeration class */
template <typename Enumeration>
constexpr inline typename std::underlying_type<Enumeration>::type getEnumClassValue(
    Enumeration const value) {
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename E>
using enable_enum_t =
    typename std::enable_if<std::is_enum<E>::value,
                            typename std::underlying_type<E>::type>::type;

template <typename E>
constexpr inline enable_enum_t<E> underlying_value(E e) noexcept {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

/* build enum class from value */
template <typename E, typename T>
constexpr inline typename std::enable_if<
    std::is_enum<E>::value && std::is_integral<T>::value, E>::type
toEnum(T value) noexcept {
  return static_cast<E>(value);
}

#endif /* UTILS_INCLUDE_DATATYPE_ENUMCLASSUTILS_HPP_ */
