#if defined(_WIN32) || defined(_WIN64)
  // disable deprecation warnings on windows 
  #define _CRT_SECURE_NO_WARNINGS
#endif

// Corresponding header
#include "utils/debug/StrError.h"

// System headers
#include <cstring>
#include <cerrno>

// Other libraries headers

// Own components headers
#include "utils/log/Log.h"

std::string strError() {
  return strerror(errno);
}