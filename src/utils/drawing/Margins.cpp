//Corresponding header
#include "utils/drawing/Margins.h"

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers

const Margins Margins::ZERO(0, 0, 0, 0);

const Margins Margins::UNDEFINED(10000, 10000, 10000, 10000);

Margins::Margins()
    : top(0), right(0), bottom(0), left(0) {

}

Margins::Margins(const int32_t _top, const int32_t _right,
                 const int32_t _bottom, const int32_t _left) {
  top = _top;
  right = _right;
  bottom = _bottom;
  left = _left;
}
