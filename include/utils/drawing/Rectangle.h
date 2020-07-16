#ifndef UTILS_RECTANGLE_H_
#define UTILS_RECTANGLE_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "utils/drawing/Point.h"

// Forward declarations

struct Rectangle {
  Rectangle();

  Rectangle(const int32_t inputX, const int32_t inputY,
            const int32_t inputW, const int32_t inputH);

  Rectangle(const Point& pos, const int32_t inputW, const int32_t inputH);

  bool operator==(const Rectangle& other) const {
    return x == other.x && y == other.y && w == other.w && h == other.h;
  }

  bool operator!=(const Rectangle& other) const {
    return !(*this == other);
  }

  Rectangle& operator-(const Rectangle& other) {
    x -= other.x;
    y -= other.y;
    w -= other.w;
    h -= other.w;

    return *this;
  }

  Rectangle& operator-=(const Rectangle& other) {
    x -= other.x;
    y -= other.y;
    w -= other.w;
    h -= other.w;

    return *this;
  }

  Rectangle& operator+(const Rectangle& other) {
    x += other.x;
    y += other.y;
    w += other.w;
    h += other.w;

    return *this;
  }

  Rectangle& operator+=(const Rectangle& other) {
    x += other.x;
    y += other.y;
    w += other.w;
    h += other.w;

    return *this;
  }

  /** @brief used to determine whether point is in the boundaries of this
   *                                                                rectangle
   *
   *  @param const Point &     - the point to be evaluated
   *  @param const Rectangle & - the boundary rectangle
   *
   *  @returns bool            - is point inside or not
   * */
  bool isPointInRect(const Point& point) const {
    return (point.x >= x) && (point.x < (x + w)) && (point.y >= y) &&
           (point.y < (y + h));
  }

  /** @brief used to determine whether point is in the boundaries of the
   *                                                       provided rectangle
   *
   *  @param const Point &     - the point to be evaluated
   *  @param const Rectangle & - the boundary rectangle
   *
   *  @returns bool            - is point inside or not
   * */
  static inline bool isPointInRect(const Point& point, const Rectangle& rect) {
    return (point.x >= rect.x) && (point.x < (rect.x + rect.w)) &&
           (point.y >= rect.y) && (point.y < (rect.y + rect.h));
  }

  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;

  static const Rectangle ZERO;
  static const Rectangle UNDEFINED;
};

#endif /* UTILS_RECTANGLE_H_ */
