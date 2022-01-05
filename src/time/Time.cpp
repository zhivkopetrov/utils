// Corresponding header
#include "utils/time/Time.h"

// C system headers

// C++ system headers
#include <cerrno>
#include <cstring>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

Time::Time() {
  if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &_startTime)) {
    LOGERR("clock_gettime() failed, reason: %s", strerror(errno));
  }

  _elapsedLastCall.tv_sec = _startTime.tv_sec;
  _elapsedLastCall.tv_nsec = _startTime.tv_nsec;
  _elapsed.tv_sec = 0;
  _elapsed.tv_nsec = 0;
}

Time& Time::getElapsed() {
  timespec now;

  if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &now)) {
    LOGERR("clock_gettime() failed, reason: %s", strerror(errno));
  }

  _elapsed.tv_sec = now.tv_sec - _elapsedLastCall.tv_sec;
  _elapsed.tv_nsec = now.tv_nsec - _elapsedLastCall.tv_nsec;

  _elapsedLastCall.tv_sec = now.tv_sec;
  _elapsedLastCall.tv_nsec = now.tv_nsec;

  if (0 > _elapsed.tv_nsec) {
    _elapsed.tv_nsec += SECOND;
    --_elapsed.tv_sec;
  }

  return *this;
}

Time& Time::getElapsedFromStart() {
  timespec now;

  if (SUCCESS != clock_gettime(CLOCK_MONOTONIC, &now)) {
    LOGERR("clock_gettime() failed, reason: %s", strerror(errno));
  }

  _elapsed.tv_sec = now.tv_sec - _startTime.tv_sec;
  _elapsed.tv_nsec = now.tv_nsec - _startTime.tv_nsec;

  if (0 > _elapsed.tv_nsec) {
    _elapsed.tv_nsec += SECOND;
    --_elapsed.tv_sec;
  }

  return *this;
}

void Time::getClockTime(timespec* outClockTime) {
  if (SUCCESS != clock_gettime(CLOCK_REALTIME, outClockTime)) {
    LOGERR("clock_gettime() failed, reason: %s", strerror(errno));
  }
}
