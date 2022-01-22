#ifndef UTILS_RNG_H_
#define UTILS_RNG_H_

// C system headers

// C++ system headers
#include <random>

// Other libraries header

// Own components headers

class Rng {
public:
  static Rng& getInstance();

  //used to seed the Rng
  int32_t init();

  // get uniformly distributed number in the range [logRange - highRange]
  int32_t getRandomNumber(int32_t lowRange, int32_t highRange);

  // get uniformly distributed number in the range [logRange - highRange]
  double getRandomNumber(double lowRange, double highRange);

private:
  Rng() = default;

  std::mt19937 _generator;
};

#endif /* UTILS_RNG_H_ */
