#ifndef UTILS_COLOR_H_
#define UTILS_COLOR_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

struct RGBA {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t a = 255;
};

class Color {
 public:
  /** Warning: if you use this constructor be sure to provide proper
   *           32bit RGBA color.
   *
   *           24bit RGB colors will be misinterpreted. If you have
   *           24bit RGB color hex that you want to use simply add
   *           two trailing FF's at the end of your 24bit hex value.
   *
   *  Example: 24bit RGB hex: 0xF100A3   should be transformed to
   *                          0xF100A3FF
   *           before passed to this constructor
   * */
  explicit Color(const uint32_t inputRgba);

  explicit Color(const uint8_t red, const uint8_t green, const uint8_t blue,
                 const uint8_t alpha = 255);

  // forbid default constructor
  Color() = delete;

   bool operator==(const Color& other) const {
    return rgba.r == other.rgba.r && rgba.g == other.rgba.g &&
           rgba.b == other.rgba.b && rgba.a == other.rgba.a;
  }

   bool operator!=(const Color& other) const { return !(*this == other); }

   uint32_t get32BitRGBA() const {
    return (rgba.r & 0xFF000000) | (rgba.g & 0x00FF0000) |
           (rgba.b & 0x0000FF00) | (rgba.a & 0x000000FF);
  }

  RGBA rgba;
};

namespace Colors {
inline const Color RED(255, 0, 0, 255);
inline const Color GREEN(0, 255, 0, 255);
inline const Color BLUE(0, 0, 255, 255);
inline const Color BLACK(0, 0, 0, 255);
inline const Color WHITE(255, 255, 255, 255);
inline const Color GRAY(192, 192, 192, 255);
inline const Color CYAN(0, 255, 255, 255);
inline const Color MAGENTA(255, 0, 255, 255);
inline const Color YELLOW(255, 255, 0, 255);
inline const Color ORANGE(255, 128, 0, 255);
inline const Color PURPLE(128, 0, 128, 255);
inline const Color DARK_GREEN(6, 65, 14, 255);
inline const Color CARAMEL_GOLD(254, 213, 151, 255);
inline const Color FULL_TRANSPARENT(0, 0, 0, 0);
inline const Color FIRE(226, 88, 34, 0);
inline const Color SMOKE(105, 105, 105, 0);
inline const Color ICE(212, 239, 235, 0);
inline const Color LIGHTNING(192, 192, 192, 0);
}  // namespace Colors

#endif /* UTILS_COLOR_H_ */
