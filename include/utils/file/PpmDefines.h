#ifndef UTILS_PPMDEFINES_H_
#define UTILS_PPMDEFINES_H_

// System headers
#include <cstdint>
#include <string_view>

// Other libraries headers

// Own components headers
#include "utils/Log.h"

// Forward declarations

constexpr auto P3_HEADER_VALUE = "P3";
constexpr auto P6_HEADER_VALUE = "P6";

enum class PpmVersion { P3, P6 };

struct PpmHeader {
  PpmVersion version = PpmVersion::P6;
  uint32_t imageWidth{};
  uint32_t imageHeight{};
  uint32_t maxColorComponent = 255;
};

inline PpmVersion toPpmVersion(std::string_view str) {
  if (P3_HEADER_VALUE == str) {
    return PpmVersion::P3;
  }

  if (P6_HEADER_VALUE == str) {
    return PpmVersion::P6;
  }

  LOGERR(
      "Received unsupported PpmVersion: [%s]. Falling back to PpmVersion::P3",
      str.data());
  return PpmVersion::P3;
}

#endif /* UTILS_PPMDEFINES_H_ */