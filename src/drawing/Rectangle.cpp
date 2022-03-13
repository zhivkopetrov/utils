// Corresponding header
#include "utils/drawing/Rectangle.h"

// System headers

// Other libraries headers

// Own components headers

Rectangle::Rectangle()
    : x(0), y(0), w(0), h(0) {
}

Rectangle::Rectangle(const int32_t inputX, const int32_t inputY,
                     const int32_t inputW, const int32_t inputH)
    : x(inputX), y(inputY), w(inputW), h(inputH) {
}

Rectangle::Rectangle(const Point &pos, const int32_t inputW,
                     const int32_t inputH)
    : x(pos.x), y(pos.y), w(inputW), h(inputH) {
}

bool Rectangle::operator==(const Rectangle &other) const {
  return x == other.x && y == other.y && w == other.w && h == other.h;
}

bool Rectangle::operator!=(const Rectangle &other) const {
  return ! (*this == other);
}

Rectangle& Rectangle::operator-(const Rectangle &other) {
  x -= other.x;
  y -= other.y;
  w -= other.w;
  h -= other.w;

  return *this;
}

Rectangle& Rectangle::operator-=(const Rectangle &other) {
  x -= other.x;
  y -= other.y;
  w -= other.w;
  h -= other.w;

  return *this;
}

Rectangle& Rectangle::operator+(const Rectangle &other) {
  x += other.x;
  y += other.y;
  w += other.w;
  h += other.w;

  return *this;
}

Rectangle& Rectangle::operator+=(const Rectangle &other) {
  x += other.x;
  y += other.y;
  w += other.w;
  h += other.w;

  return *this;
}

bool Rectangle::isPointInRect(const Point &point) const {
  return (point.x >= x) && (point.x < (x + w)) && (point.y >= y)
         && (point.y < (y + h));
}

bool Rectangle::isPointInRect(const Point &point, const Rectangle &rect) {
  return (point.x >= rect.x) && (point.x < (rect.x + rect.w))
         && (point.y >= rect.y) && (point.y < (rect.y + rect.h));
}

