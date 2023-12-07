#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

// System headers
#include <cinttypes>
#include <cstdarg>
#include <cstdio>

// Other libraries headers

// Own components headers
#include "utils/LogBase.h"

// Forward Declarations

#define LOGERR(format, ...)                                              \
  do {                                                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BOLD_RED); \
    printf("%s(%s:%d): " format "\n", __func__, __FILE__, __LINE__,      \
           ##__VA_ARGS__);                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);     \
    fflush(stdout);                                                      \
  } while (0)

#define LOG(format, ...)                \
  do {                                  \
    printf(format "\n", ##__VA_ARGS__); \
    fflush(stdout);                     \
  } while (0)

#define LOG_ON_SAME_LINE(format, ...) \
  do {                                \
    printf(format, ##__VA_ARGS__);    \
    fflush(stdout);                   \
  } while (0)

#define LOGG(format, ...)                                             \
  do {                                                                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::GREEN); \
    printf(format "\n", ##__VA_ARGS__);                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);  \
    fflush(stdout);                                                   \
  } while (0)

#define LOGG_ON_SAME_LINE(format, ...)                                \
  do {                                                                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::GREEN); \
    printf(format, ##__VA_ARGS__);                                    \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);  \
    fflush(stdout);                                                   \
  } while (0)

#define LOGY(format, ...)                                              \
  do {                                                                 \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::YELLOW); \
    printf(format "\n", ##__VA_ARGS__);                                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                     \
  } while (0)

#define LOGY_ON_SAME_LINE(format, ...)                                 \
  do {                                                                 \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::YELLOW); \
    printf(format, ##__VA_ARGS__);                                     \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGB(format, ...)                                            \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BLUE); \
    printf(format "\n", ##__VA_ARGS__);                              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGB_ON_SAME_LINE(format, ...)                               \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BLUE); \
    printf(format, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGM(format, ...)                                               \
  do {                                                                  \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::MAGENTA); \
    printf(format "\n", ##__VA_ARGS__);                                 \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);    \
    fflush(stdout);                                                     \
  } while (0)

#define LOGM_ON_SAME_LINE(format, ...)                                  \
  do {                                                                  \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::MAGENTA); \
    printf(format, ##__VA_ARGS__);                                      \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);    \
    fflush(stdout);                                                     \
  } while (0)

#define LOGC(format, ...)                                            \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::CYAN); \
    printf(format "\n", ##__VA_ARGS__);                              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGC_ON_SAME_LINE(format, ...)                               \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::CYAN); \
    printf(format, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGR(format, ...)                                            \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::RED);  \
    printf(format "\n", ##__VA_ARGS__);                              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGR_ON_SAME_LINE(format, ...)                               \
  do {                                                               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::RED);  \
    printf(format, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#endif /* UTILS_LOG_H_ */
