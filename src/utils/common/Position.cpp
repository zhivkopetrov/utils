// Corresponding header
#include "utils/common/Position.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"

Point Position::getCentral(const Rectangle& rec, const int32_t width,
                           const int32_t height) {
  Point central;

  central.x = getMiddleX(rec.x, rec.w, width);
  central.y = getMiddleY(rec.y, rec.h, height);

  return central;
}

Point Position::getRightMiddle(const Rectangle& rec, const int32_t width,
                               const int32_t height) {
  Point rightMiddle;

  rightMiddle.x = getRightX(rec.x, rec.w, width);
  rightMiddle.y = getMiddleY(rec.y, rec.h, height);

  return rightMiddle;
}
