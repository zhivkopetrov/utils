// Corresponding header
#include "utils/drawing/Color.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

namespace Colors {
const Color RED(255, 0, 0, 255);
const Color GREEN(0, 255, 0, 255);
const Color BLUE(0, 0, 255, 255);
const Color BLACK(0, 0, 0, 255);
const Color WHITE(255, 255, 255, 255);
const Color GRAY(192, 192, 192, 255);
const Color CYAN(0, 255, 255, 255);
const Color MAGENTA(255, 0, 255, 255);
const Color YELLOW(255, 255, 0, 255);
const Color ORANGE(255, 128, 0, 255);
const Color PURPLE(128, 0, 128, 255);
const Color DARK_GREEN(6, 65, 14, 255);
const Color CARAMEL_GOLD(254, 213, 151, 255);
const Color FULL_TRANSPARENT(0, 0, 0, 0);
const Color FIRE(226, 88, 34, 0);
const Color SMOKE(105, 105, 105, 0);
const Color ICE(212, 239, 235, 0);
const Color LIGHTNING(192, 192, 192, 0);
}  // namespace Colors

Color::Color(const uint32_t inputRgba) {
  rgba.r = static_cast<uint8_t>( (inputRgba & 0xFF000000) >> 24);
  rgba.g = static_cast<uint8_t>( (inputRgba & 0x00FF0000) >> 16);
  rgba.b = static_cast<uint8_t>( (inputRgba & 0x0000FF00) >> 8);
  rgba.a = static_cast<uint8_t>( (inputRgba & 0x000000FF));
}

Color::Color(const uint8_t red, const uint8_t green, const uint8_t blue,
             const uint8_t alpha) {
  rgba.r = red;
  rgba.g = green;
  rgba.b = blue;
  rgba.a = alpha;
}
