// Corresponding header
#include "utils/drawing/Rectangle.h"

// C system headers

// C++ system headers

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

const Rectangle Rectangle::ZERO(0, 0, 0, 0);
const Rectangle Rectangle::UNDEFINED(100000, 100000, 100000, 100000);
