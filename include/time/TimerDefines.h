#ifndef UTILS_INCLUDE_TIME_TIMERDEFINES_H_
#define UTILS_INCLUDE_TIME_TIMERDEFINES_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

// how many nanoseconds are there in single unit of time
enum TimeUnits {
  SECOND = 1000000000,
  MILLISECOND = 1000000,
  MICROSECOND = 1000,
  NANOSECOND = 1
};

#endif /* UTILS_INCLUDE_TIME_TIMERDEFINES_H_ */
