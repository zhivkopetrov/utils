#ifndef UTILS_MARGIN_H
#define UTILS_MARGIN_H

//System headers
#include <cstdint>

//Other libraries headers

//Own components headers

struct Margin {
public:
  Margin();

  Margin(int32_t inpuTop, int32_t inputRight, int32_t inputBottom,
          int32_t inputLeft);

  int32_t top;
  int32_t right;
  int32_t bottom;
  int32_t left;
};

namespace Margins {
inline const Margin ZERO(0, 0, 0, 0);
inline const Margin UNDEFINED(10000, 10000, 10000, 10000);
} //namespace Margins

#endif //UTILS_MARGIN_H
