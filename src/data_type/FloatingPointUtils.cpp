// Corresponding header
#include "utils/data_type/FloatingPointUtils.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/data_type/FloatingPoint.h"

float FloatingPointUtils::kahanSummation(float* begin, const uint64_t SIZE) {
  // Beware overly-aggressive compiler optimisations!
  volatile float result = 0.0f;

  // A running compensation for lost low-order bits.
  float compensation = 0.0f;

  float y = 0.0f;
  float t = 0.0f;

  for (size_t i = 0; i < SIZE; ++i) {
    // So far, so good: c is zero.
    y = begin[i] - compensation;

    // Alas, result is big, y small, so low-order digits of y are lost.
    t = result + y;

    //(t - result) cancels the high-order part of y;
    // subtracting y recovers negative (low part of y)
    compensation = (t - result) - y;

    // Algebraically, compensation should always be zero.
    result = t;

    // Next time around, the lost low part will be added
    // to y in a fresh attempt (new iteration).
  }

  return result;
}

double FloatingPointUtils::kahanSummation(double* begin, const uint64_t SIZE) {
  // Beware overly-aggressive compiler optimisations!
  volatile double result = 0.0;

  // A running compensation for lost low-order bits.
  double compensation = 0.0;

  double y = 0.0;
  double t = 0.0;

  for (size_t i = 0; i < SIZE; ++i) {
    // So far, so good: c is zero.
    y = begin[i] - compensation;

    // Alas, result is big, y small, so low-order digits of y are lost.
    t = result + y;

    //(t - result) cancels the high-order part of y;
    // subtracting y recovers negative (low part of y)
    compensation = (t - result) - y;

    // Algebraically, compensation should always be zero.
    result = t;

    // Next time around, the lost low part will be added
    // to y in a fresh attempt (new iteration).
  }

  return result;
}

bool FloatingPointUtils::areAlmostEqual(const float first, const float second) {
  const FloatingPoint<float> lhs(first);
  const FloatingPoint<float> rhs(second);

  return lhs.AlmostEquals(rhs);
}

bool FloatingPointUtils::areAlmostEqual(const double first,
                                        const double second) {
  const FloatingPoint<double> lhs(first);
  const FloatingPoint<double> rhs(second);

  return lhs.AlmostEquals(rhs);
}
