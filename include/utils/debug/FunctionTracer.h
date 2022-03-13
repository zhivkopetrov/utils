#ifndef UTILS_FUNCTIONTRACER_H_
#define UTILS_FUNCTIONTRACER_H_

/*
 * FunctionTracer.h
 * Generic class for tracing the function calls
 *      Example of usage:
 *
 * In someFile.cpp
 *
 * #define TRACING_ENABLED 1
 *
 * #include "FunctionTracer.hpp"
 *
 * void foo()
 * {
 *     TRACE_ENTRY_EXIT;
 *
 *     //your source
 * }
 */

#if defined(DEEP_TRACING_ENABLED)
// System headers
#include <cstdio>
#include <ctime>

// Other libraries headers

// Own components headers

// Forward declarations

#define BUFF_SIZE 26

class FunctionTracer {
 public:
  explicit FunctionTracer(const char* file, const char* func)
      : _fileName(file), _funcName(func), _tm_info(nullptr), _timer(0) {
    time(&_timer);
    _tm_info = localtime(&_timer);
    strftime(_buffer, BUFF_SIZE, "%Y-%m-%d %H:%M:%S", _tm_info);

    printf(">> %s, [%s], [%s]\n", _funcName, _buffer, _fileName);
    fflush(stdout);
  }

  ~FunctionTracer() {
    time(&_timer);
    _tm_info = localtime(&_timer);
    strftime(_buffer, BUFF_SIZE, "%Y-%m-%d %H:%M:%S", _tm_info);

    printf("<< %s, [%s], [%s]\n", _funcName, _buffer, _fileName);
    fflush(stdout);
  }

 private:
  const char* _fileName;
  const char* _funcName;
  struct tm* _tm_info;
  time_t _timer;
  char _buffer[BUFF_SIZE];
};

#define TRACE_ENTRY_EXIT_FOR(file, func) FunctionTracer name(file, func)
#define TRACE_ENTRY_EXIT TRACE_ENTRY_EXIT_FOR(__FILE__, __PRETTY_FUNCTION__)

#else /* DEEP_TRACING_ENABLED */
#if defined(TRACING_ENABLED)

#include <cstdio>

class FunctionTracer {
 public:
  explicit FunctionTracer(const char* func) : _funcName(func) {
    printf(">> %s\n", _funcName);
    fflush(stdout);
  }

  ~FunctionTracer() {
    printf("<< %s\n", _funcName);
    fflush(stdout);
  }

 private:
  const char* _funcName;
};

#define TRACE_ENTRY_EXIT_FOR(func) FunctionTracer name(func)
#define TRACE_ENTRY_EXIT TRACE_ENTRY_EXIT_FOR(__PRETTY_FUNCTION__)

#else /* TRACING_ENABLED */

/* Release Macro expands to nothing -> no performance cost */
#define TRACE_ENTRY_EXIT

#endif /* TRACING_ENABLED */

#endif /* DEEP_TRACING_ENABLED */

#endif /* UTILS_FUNCTIONTRACER_H_ */
