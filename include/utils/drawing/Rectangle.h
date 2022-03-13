#ifndef UTILS_RECTANGLE_H_
#define UTILS_RECTANGLE_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "utils/drawing/Point.h"

// Forward declarations

struct Rectangle {
  Rectangle();

  Rectangle(const int32_t inputX, const int32_t inputY, const int32_t inputW,
            const int32_t inputH);

  Rectangle(const Point &pos, const int32_t inputW, const int32_t inputH);

  bool operator==(const Rectangle &other) const;
  bool operator!=(const Rectangle &other) const;
  Rectangle& operator-(const Rectangle &other);
  Rectangle& operator-=(const Rectangle &other);
  Rectangle& operator+(const Rectangle &other);
  Rectangle& operator+=(const Rectangle &other);

  /** @brief used to determine whether point is in the boundaries of this
   *                                                                rectangle
   *
   *  @param const Point &     - the point to be evaluated
   *  @param const Rectangle & - the boundary rectangle
   *
   *  @returns bool            - is point inside or not
   * */
  bool isPointInRect(const Point &point) const;

  /** @brief used to determine whether point is in the boundaries of the
   *                                                       provided rectangle
   *
   *  @param const Point &     - the point to be evaluated
   *  @param const Rectangle & - the boundary rectangle
   *
   *  @returns bool            - is point inside or not
   * */
  static bool isPointInRect(const Point &point, const Rectangle &rect);

  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
};

namespace Rectangles {
const Rectangle ZERO(0, 0, 0, 0);
const Rectangle UNDEFINED(100000, 100000, 100000, 100000);
} //namespace Rectangles

#endif /* UTILS_RECTANGLE_H_ */
