#ifndef UTILS_INCLUDE_DRAWING_POINT_H_
#define UTILS_INCLUDE_DRAWING_POINT_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

struct Point {
  Point() : x(0), y(0) {}

  explicit Point(const int32_t inputX, const int32_t inputY)
      : x(inputX), y(inputY) {}

  inline bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  inline bool operator!=(const Point& other) const { return !(*this == other); }

  inline Point& operator+(const Point& other) {
    x += other.x;
    y += other.y;

    return *this;
  }

  inline Point& operator+=(const Point& other) {
    x += other.x;
    y += other.y;

    return *this;
  }

  inline Point& operator-(const Point& other) {
    x -= other.x;
    y -= other.y;

    return *this;
  }

  inline Point& operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;

    return *this;
  }

  int32_t x;
  int32_t y;

  static const Point ZERO;
  static const Point UNDEFINED;
};

#endif /* UTILS_INCLUDE_DRAWING_POINT_H_ */
