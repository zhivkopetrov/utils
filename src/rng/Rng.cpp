// Corresponding header
#include "utils/rng/Rng.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

Rng& Rng::getInstance() {
  static Rng rng;
  return rng;
}

int32_t Rng::init() {
  std::random_device rd;
  _generator.seed(rd());

  return SUCCESS;
}

int32_t Rng::getRandomNumber(int32_t lowRange, int32_t highRange) {
  std::uniform_int_distribution<> distr(lowRange, highRange);
  return distr(_generator);
}

// get uniformly distributed number in the range [logRange - highRange]
double Rng::getRandomNumber(double lowRange, double highRange) {
  std::uniform_real_distribution<> distr(lowRange, highRange);
  return distr(_generator);
}
