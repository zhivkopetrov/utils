#ifndef UTILS_ENUMCLASSUTILS_H_
#define UTILS_ENUMCLASSUTILS_H_

// System headers
#include <type_traits>

// Other libraries headers

// Own components headers

// Forward declarations

// extract value from enumeration class
template <typename Enumeration>
constexpr auto getEnumValue(Enumeration const value) {
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// build enum class from value
template <typename E, typename T>
  constexpr inline auto toEnum(T value) noexcept {
  static_assert(std::is_enum<E>::value, "Type should be enum!");
  static_assert(std::is_integral<T>::value, "Type should be integral!");
  return static_cast<E>(value);
}

struct EnumClassHash {
    template <typename T>
    inline std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

#endif /* UTILS_ENUMCLASSUTILS_H_ */
