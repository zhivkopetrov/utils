#ifndef UTILS_POINT_H_
#define UTILS_POINT_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

struct Point {
  Point();

  Point(const int32_t inputX, const int32_t inputY);

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  Point& operator+(const Point& other);
  Point& operator+=(const Point& other);
  Point& operator-(const Point& other);
  Point& operator-=(const Point& other);

  int32_t x;
  int32_t y;
};

namespace Points {
inline const Point ZERO(0, 0);
inline const Point UNDEFINED(100000, 100000);
} //namespace Points

#endif /* UTILS_POINT_H_ */
