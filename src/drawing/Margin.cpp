//Corresponding header
#include "utils/drawing/Margin.h"

//System headers

//Other libraries headers

//Own components headers

Margin::Margin()
    : top(0), right(0), bottom(0), left(0) {

}

Margin::Margin(int32_t inpuTop, int32_t inputRight, int32_t inputBottom,
               int32_t inputLeft)
    : top(inpuTop), right(inputRight), bottom(inputBottom), left(inputLeft) {

}
