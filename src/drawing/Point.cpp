// Corresponding header
#include "utils/drawing/Point.h"

// System headers

// Other libraries headers

// Own components headers

Point::Point()
    : x(0), y(0) {
}

Point::Point(const int32_t inputX, const int32_t inputY)
    : x(inputX), y(inputY) {
}

bool Point::operator==(const Point &other) const {
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
  return ! (*this == other);
}

Point& Point::operator+(const Point &other) {
  x += other.x;
  y += other.y;

  return *this;
}

Point& Point::operator+=(const Point &other) {
  x += other.x;
  y += other.y;

  return *this;
}

Point& Point::operator-(const Point &other) {
  x -= other.x;
  y -= other.y;

  return *this;
}

Point& Point::operator-=(const Point &other) {
  x -= other.x;
  y -= other.y;

  return *this;
}
