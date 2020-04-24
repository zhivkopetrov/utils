#ifndef UTILS_INCLUDE_DATATYPE_INTEGERUTILS_H_
#define UTILS_INCLUDE_DATATYPE_INTEGERUTILS_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

class IntegerUtils {
 public:
  IntegerUtils() = delete;

  /**
   * @brief the function returns the count of all digits in
   *      the passed number
   *
   * @param the number, from which to extract the digits count
   */
  static uint8_t getDigitsCount(const uint64_t number);

  /** @brief used to acquire the next higher power of 2
   *
   *  @param uint32_t  - input number to be evaluated
   *
   *  @return uint32_t - next higher power of 2
   *
   *         NOTE: this method contains some evil bitwise magic
   *                                 optimised for 32bit unsigned numbers
   * */
  static uint32_t getNextPowerOfTwo(uint32_t number);

  /** @brief used to acquire the next higher power of 2
   *
   *  @param const uint64_t  - input number to be evaluated
   *
   *  @return uint64_t       - next higher power of 2
   * */
  static uint64_t getNextPowerOfTwo(const uint64_t number);
};

#endif /* UTILS_INCLUDE_DATATYPE_INTEGERUTILS_H_ */
