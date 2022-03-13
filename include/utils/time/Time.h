#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

// System headers
#include <cstdint>
#include <chrono>

// Other libraries headers

// Own components headers

// Forward Declarations

class Time {
public:
  Time& getElapsed();

  int64_t toSeconds() const;
  int64_t toMilliseconds() const;
  int64_t toMicroseconds() const;
  int64_t toNanoseconds() const;

private:
  std::chrono::time_point<std::chrono::steady_clock> _now =
      std::chrono::steady_clock::now();
  std::chrono::time_point<std::chrono::steady_clock> _elapsedLastCall;
};

#endif /* UTILS_TIME_H_ */
