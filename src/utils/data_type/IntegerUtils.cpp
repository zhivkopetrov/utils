// Corresponding .h file
#include "utils/data_type/IntegerUtils.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

uint8_t IntegerUtils::getDigitsCount(const uint64_t number) {
  if (0 == number) {
    return 1;
  }

  uint8_t digitsCnt = 0;

  uint64_t localNumber = number;

  while (localNumber != 0) {
    localNumber /= 10;
    ++digitsCnt;
  }

  return digitsCnt;
}

uint32_t IntegerUtils::getNextPowerOfTwo(uint32_t number) {
  --number;
  number |= number >> 1;
  number |= number >> 2;
  number |= number >> 4;
  number |= number >> 8;
  number |= number >> 16;
  ++number;

  return number;
}

uint64_t IntegerUtils::getNextPowerOfTwo(const uint64_t number) {
  uint64_t power = 1;
  while (power < number) {
    power <<= 1;
  }

  return power;
}
