// Corresponding header
#include "utils/drawing/Color.h"

// System headers

// Other libraries headers

// Own components headers

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
