#ifndef UTILS_MARGINS_H
#define UTILS_MARGINS_H
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

struct Margins {
public:
  Margins();

  Margins(const int32_t top, const int32_t right, const int32_t bottom,
          const int32_t left);

  int32_t top;
  int32_t right;
  int32_t bottom;
  int32_t left;

  static const Margins ZERO;
  static const Margins UNDEFINED;
};

#endif //UTILS_MARGINS_H
