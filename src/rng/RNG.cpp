/**
 * RNG.cpp
 * class RNG - Implementation
 */

// Corresponding header
#include "rng/RNG.h"

// C system headers

// C++ system headers
#include <limits>

// Other libraries headers

// Own components headers

RNG::RNG() : _skipRange(7) {}

int32_t RNG::initialize() {
  try {
    std::random_device devUrand("/dev/urandom");

    std::uniform_int_distribution<uint32_t> range(
        0, std::numeric_limits<uint32_t>::max());

    uint32_t seed = range(devUrand);

    std::srand(seed);
    double r = (static_cast<double>(std::rand()) / RAND_MAX);
    uint32_t mtSeed =
        static_cast<uint32_t>(r * std::numeric_limits<uint32_t>::max());

    _mtRng.seed(mtSeed);
    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    return EXIT_FAILURE;
  }
}

void RNG::process() {
  _getRandomNumber();
}

uint64_t RNG::_getRandomNumber() {
   for ( int32_t i = rand() % _skipRange; i > 0; --i ) {
     _mtRng();
   }

  return _mtRng();
}

uint32_t RNG::getNumber(const uint32_t range) {
  uint32_t number = 0;

  // Check for 0 is necessary to avoid division by 0
  // Check for 1 is necessary for the optimization
  //      ranges to be a 32 bit unsigned int
  // There is a requirement that no calls be made to
  //      the generator if range is less than 2
  if (2 <= range) {
    const int64_t c2_32 = 0x1LLU << 32;
    int64_t maxAcceptable = c2_32 - (c2_32 % range);
    uint32_t ranges = static_cast<uint32_t>(maxAcceptable / range);

    // Avoid bias
    do {
      number = static_cast<uint32_t>(_getRandomNumber());
    } while (static_cast<int64_t>(number) >= maxAcceptable);

    number = number / ranges;
  }

  return number;
}

int32_t RNG::getCombination(int32_t* array, const uint32_t arraySize,
                            const uint32_t elementCount) {
  if (elementCount > arraySize) {
    return 1;
  }

  for (uint32_t i = 0; i < elementCount; ++i) {
    if (arraySize - i == 1) {
      break;
    }

    uint32_t tempIdx = i + getNumber(arraySize - i);

    std::swap(array[i], array[tempIdx]);
  }

  return 0;
}

int32_t RNG::shuffleArray(int32_t* array, const uint32_t size) {
  return getCombination(array, size, size);
}

int32_t RNG::generateSequence(const uint32_t count, uint32_t* array,
                              const uint32_t range, const bool decreaseRange) {
  if (decreaseRange && (count > range)) {
    return 1;
  }

  for (uint32_t i = 0; i < count; ++i) {
    array[i] = getNumber(range - (decreaseRange ? i : 0));
  }

  return 0;
}
