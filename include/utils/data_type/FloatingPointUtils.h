#ifndef UTILS_FLOATINGPOINTUTILS_H_
#define UTILS_FLOATINGPOINTUTILS_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

class FloatingPointUtils {
 public:
  FloatingPointUtils() = delete;

  static bool hasSameSign(const double a, const double b);

  //===================== START KAHAN SUMMATION ==========================

  /** Summary:
   *      Floating point operations such as division or multiplication are
   *      considered precision safe.
   *
   *      Floating point operations such as addition or subtraction
   *      generate huge error in precision.
   *      Therefore when big number of additions/subtraction need to be
   *      made the error is bigger.
   *
   *      The Kahan summation algorithm minimises the error to ~ 0.0
   *      For the algorithm to work we need to have the numbers we want
   *      to add/subtract stored.
   * */

  /** @brief used to sum array of floating pointer numbers with minimum
   *                                        error in precision generated.
   *
   *  @param float *        - the beginning of float's array
   *  @param const uint64_t - the size of the array
   *
   *  @return float         - the result of the summation
   *
   *         NOTE: if you are using "std::vector<float> vec" as a
   *               container invoke this function with
   *               float result = kahanSummation(vec.data(), vec.size());
   * */
  static float kahanSummation(float* begin, const uint64_t SIZE);

  /** @brief used to sum array of floating pointer numbers with minimum
   *                                        error in precision generated.
   *
   *  @param double *        - the beginning of float's array
   *  @param const uint64_t  - the size of the array
   *
   *  @return double         - the result of the summation
   *
   *         NOTE: if you are using "std::vector<double> vec" as a
   *               container invoke this function with
   *               double result = kahanSummation(vec.data(), vec.size());
   * */
  static double kahanSummation(double* begin, const uint64_t SIZE);

  //====================== END KAHAN SUMMATION ===========================

  //==================== START EQUALITY FUNCTIONS ========================

  /** @brief used to compare two floating point numbers for "equality"
   *         NOTE: both parameters must be of the same floating point type
   *
   *  @param const float first  - first value to be evaluated
   *  @param const float second - second value to be evaluated
   *
   *  @return bool              - almost equal or not
   * */
  static bool areAlmostEqual(const float first, const float second);

  /** @brief used to compare two floating point numbers for "equality"
   *         NOTE: both parameters must be of the same floating point type
   *
   *  @param const double first  - first value to be evaluated
   *  @param const double second - second value to be evaluated
   *
   *  @return bool              - almost equal or not
   * */
  static bool areAlmostEqual(const double first, const double second);

  //===================== END EQUALITY FUNCTIONS =========================

 private:
  /** @brief used to capture bad(not of same type) input parameters
   *                                                      of the function
   * */
  template <class T>
  static bool areAlmostEqual(const T first, const float second) = delete;

  /** @brief used to capture bad(not of same type) input parameters
   *                                                      of the function
   * */
  template <class T>
  static bool areAlmostEqual(const double first, const T second) = delete;
};

#endif /* UTILS_FLOATINGPOINTUTILS_H_ */
