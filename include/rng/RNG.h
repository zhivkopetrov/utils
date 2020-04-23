/**
 * RNG.h
 * class RNG - Random number generator
 * Wrapper of the mt19937 implementation in the standard library
 */

#ifndef UTILS_INCLUDE_RNG_RNG_H_
#define UTILS_INCLUDE_RNG_RNG_H_

// C system headers

// C++ system headers
#include <random>

// Other libraries headers

// Own components headers

// Forward declarations

class RNG {
 public:
  RNG();
  ~RNG() = default;

  RNG(const RNG &) = delete;
  RNG(RNG &&) = delete;
  RNG &operator=(const RNG &) = delete;
  RNG &operator=(RNG &&) = delete;

  /**
   * Initializes the seed of the RNG using the /dev/urandom file.
   * Must be called prior the actuall use of the RNG
   * @result - error code
   */
  int32_t initialize();

  /**
   * Implements the back cycling algorithm.
   * Needs to be called in the main cycle.
   */
  void process();

  /**
   * Get a number of count random values in range [0; range-1] to
   * array, pointed by numbers
   * If decreaseRange is set to true, decrease the range by 1 for each
   * following random value
   * @param  count - number of random values to get
   * @param  array - pointer to an array
   * @param  range - range of random values
   * @param  decreaseRange - decrease range for each following number if
   *                          set to true
   */
  int32_t generateSequence(const uint32_t count, uint32_t *array,
                           const uint32_t range,
                           const bool decreaseRange = false);

  /**
   * shuffle an array
   * @param  array - pointer to array
   * @param  size - size of array
   */
  int32_t shuffleArray(int32_t *array, uint32_t size);

  /**
   * get a combination of array elements
   * @param array - pointer to array
   * @param arraySize - size of the whole array
   * @param elementCount - number of elements in the combination
   */
  int32_t getCombination(int32_t *array, const uint32_t arraySize,
                         const uint32_t elementCount);

  /**
   * Returns an unsigned integer random value in the range [0; range-1]
   * @param range - range must be greater that 1
   */
  uint32_t getNumber(const uint32_t range);

 private:
  /**
   * Returns an unsigned integer random value
   */
  uint64_t _getRandomNumber();

  std::mt19937 _mtRng;

  const uint32_t _skipRange;
};

#endif  // UTILS_INCLUDE_RNG_RNG_H_
