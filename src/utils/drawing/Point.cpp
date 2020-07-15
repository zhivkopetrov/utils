// Corresponding header
#include "utils/drawing/Point.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

Point::Point()
    : x(0), y(0) {
}

Point::Point(const int32_t inputX, const int32_t inputY)
    : x(inputX), y(inputY) {
}

const Point Point::ZERO(0, 0);
const Point Point::UNDEFINED(100000, 100000);
