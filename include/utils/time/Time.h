#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <ctime>

// Other libraries headers

// Own components headers
#include "utils/time/TimerDefines.h"

class Time {
 public:
  Time();
  ~Time() = default;

  /** @brief used to measure elapsed time since last invoke of this method
   *         NOTE: .getElapsed() method simply measures time between 2
   *         points of time. In order to display this time chain the
   *         function with one of the below display functions.
   *         Example:
   *         Time time;
   *
   *         //something you want to measure
   *
   *         const int64_t elapsedTime =
   *                                   time.getElapsed().toMilliseconds();
   *
   *  @returns Time & - *this instance
   * */
  Time& getElapsed();

  /** @brief used to measure elapsed time since the creation of
   *                                                   the Time instance.
   *         NOTE: In order to display this time chain the
   *         function with one of the below display functions.
   *         Example:
   *         Time time;
   *
   *         //something you want to measure
   *
   *         const int64_t elapsedTime =
   *                               time.getElapsedFromStart().toSeconds();
   *
   *  @returns Time & - *this instance
   * */
  Time& getElapsedFromStart();

  /** @brief used to display the elapsed time between two calls of the
   *         .getElapsed() method in nanoseconds
   *
   *  @returns int64_t - elapsed time in nanoseconds
   * */
  inline int64_t toNanoseconds() const {
    return _elapsed.tv_sec * NANOSECOND + _elapsed.tv_nsec;
  }

  /** @brief used to display the elapsed time between two calls of the
   *         .getElapsed() method in microseconds
   *
   *  @returns int64_t - elapsed time in microseconds
   * */
  inline int64_t toMicroseconds() const {
    return _elapsed.tv_sec * MILLISECOND + _elapsed.tv_nsec / MICROSECOND;
  }

  /** @brief used to display the elapsed time between two calls of the
   *         .getElapsed() method in milliseconds
   *
   *  @returns int64_t - elapsed time in milliseconds
   * */
  inline int64_t toMilliseconds() const {
    return _elapsed.tv_sec * MICROSECOND + _elapsed.tv_nsec / MILLISECOND;
  }

  /** @brief used to display the elapsed time between two calls of the
   *         .getElapsed() method in seconds
   *
   *  @returns int64_t - elapsed time in seconds
   * */
  inline int64_t toSeconds() const { return _elapsed.tv_sec; }

  /** @brief used to acquiare system clock time with
   *                                          getClockTime kernel invoke
   *
   *  @param timespec * - populated timespec struct
   * */
  static void getClockTime(timespec* outClockTime);

  /** @brief used to get unique timestamp (seconds precision)
   *
   *  @returns int64_t - unique timestamp (in seconds)
   * */
  inline static int64_t getTimestamp() { return time(0); }

  /** @brief used to display the value of input timespec in nanoseconds
   *
   *  @param const timespec & - timespec struct to be converted
   *
   *  @returns int64_t        - value of input timespec in nanoseconds
   * */
  inline static int64_t toNanoseconds(const timespec& ts) {
    return ts.tv_sec * NANOSECOND + ts.tv_nsec;
  }

  /** @brief used to display the value of input timespec in microseconds
   *
   *  @param const timespec & - timespec struct to be converted
   *
   *  @returns int64_t        - value of input timespec in microseconds
   * */
  inline static int64_t toMicroseconds(const timespec& ts) {
    return ts.tv_sec * MILLISECOND + ts.tv_nsec / MICROSECOND;
  }

  /** @brief used to display the value of input timespec in milliseconds
   *
   *  @param const timespec & - timespec struct to be converted
   *
   *  @returns int64_t        - value of input timespec in milliseconds
   * */
  inline static int64_t toMilliseconds(const timespec& ts) {
    return ts.tv_sec * MICROSECOND + ts.tv_nsec / MILLISECOND;
  }

  /** @brief used to display the value of input timespec in seconds
   *
   *  @param const timespec & - timespec struct to be converted
   *
   *  @returns int64_t        - value of input timespec in seconds
   * */
  inline static int64_t toSeconds(const timespec& ts) { return ts.tv_sec; }

 private:
  // used to measure time from the creation of the Time instance
  timespec _startTime;

  // used to measure elapsed time since last getElapsed() call
  timespec _elapsed;

  // used to help calculate the elapsed time since last getElapsed() call
  timespec _elapsedLastCall;
};

#endif /* UTILS_TIME_H_ */
