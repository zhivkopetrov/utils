#ifndef UTILS_LOGBASE_H_
#define UTILS_LOGBASE_H_

// System headers
#include <cinttypes>
#include <cstdarg>
#include <cstdio>

// Other libraries headers

// Own components headers

// Forward Declarations

namespace LogInternal {

enum class TerminalColor {
  NONE,
  RED,
  GREEN,
  BLUE,
  YELLOW,
  MAGENTA,
  CYAN,
  BOLD_RED
};

void setTerminalColor(TerminalColor color);

} //namespace LogInternal

#endif /* UTILS_LOGBASE_H_ */
