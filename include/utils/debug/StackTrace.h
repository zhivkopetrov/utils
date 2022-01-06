#ifndef UTILS_STACKTRACE_HPP_
#define UTILS_STACKTRACE_HPP_

// C system headers
#include <cxxabi.h>
#include <execinfo.h>

// C++ system headers
#include <cstdint>
#include <cstdio>
#include <cstdlib>

// Other libraries headers

// Own components headers
#include "utils/Log.h"

/** Print a demangled stack backtrace of the caller function */
static void printStacktrace(const int32_t maxFrames = 127) {
  const int32_t MAX_FRAMES_INTERNAL = maxFrames + 1;

  // storage array for stack trace address data
  void *addrList[MAX_FRAMES_INTERNAL];

  // retrieve current stack addresses
  int32_t addrLen = backtrace(addrList, MAX_FRAMES_INTERNAL);

  if (0 == addrLen) {
    LOGERR("Empty stack trace, possibly corrupt");

    return;
  }

  // resolve addresses into strings containing "filename(function + address)"
  // this array must be free()-ed
  char **symbolList = backtrace_symbols(addrList, addrLen);

  // allocate string which will be filled with the demangled function name
  size_t FUNC_NAME_SIZE = 256;

  char *funcName = (char *)malloc(FUNC_NAME_SIZE);
  char *beginName = nullptr;
  char *beginOffset = nullptr;
  char *endOffset = nullptr;

  // iterate over the returned symbol lines. skip the first, it is the
  // address of this function.
  for (int32_t i = 1; i < addrLen; ++i) {
    LOG_ON_SAME_LINE("[%d] ", i - 1);

    beginName = nullptr;
    beginOffset = nullptr;
    endOffset = nullptr;

    // find parentheses and +address offset surrounding the mangled name:
    for (char *p = symbolList[i]; *p; ++p) {
      if (*p == '(') {
        beginName = p;
      } else if (*p == '+') {
        beginOffset = p;
      } else if (*p == ')' && beginOffset) {
        endOffset = p;

        break;
      }
    }

    if (beginName && beginOffset && endOffset && beginName < beginOffset) {
      *beginName++ = '\0';
      *beginOffset++ = '\0';
      *endOffset = '\0';

      // mangled name is now in [begin_name, begin_offset) and caller
      // offset in [begin_offset, end_offset). now apply
      //__cxa_demangle():
      int32_t status = 0;
      char *ret =
          abi::__cxa_demangle(beginName, funcName, &FUNC_NAME_SIZE, &status);
      if (0 == status) {
        funcName = ret;  // use possibly realloc()-ed string

        LOG("%s : %s+%s", symbolList[i], funcName, beginOffset);
      } else {
        // demangling failed. Output function name as a C function with
        // no arguments.
        LOG("%s : %s()+%s", symbolList[i], beginName, beginOffset);
      }
    } else {
      // couldn't parse the line -> print the whole line.
      LOG("%s", symbolList[i]);
    }
  }

  if (funcName)  // sanity check
  {
    free(funcName);
    funcName = nullptr;
  }

  if (symbolList)  // sanity check
  {
    free(symbolList);
    symbolList = nullptr;
  }
}

#endif /* UTILS_STACKTRACE_HPP_ */
