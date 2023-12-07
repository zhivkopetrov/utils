#ifndef UTILS_TIMEDLOG_H_
#define UTILS_TIMEDLOG_H_

// System headers
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <ctime>

// Other libraries headers

// Own components headers
#include "utils/log/LogBase.h"
#include "utils/time/LocalTime.h"

// Forward Declarations

// function below carry a timestamp in the beginning of the message with format
//"%Y-%m-%d %H:%M:%S"

#define POPULATE_TIME_BUFFER(buffer) \
    time_t timer;                                                   \
    time(&timer);                                                   \
    const std::tm tmInfo = localtime_secure(timer);                 \
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tmInfo); \


#define LOGERR_T(format, ...)                                            \
  do {                                                                   \
    char buffer[26];                                                     \
    POPULATE_TIME_BUFFER(buffer);                                        \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BOLD_RED); \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__,   \
           __LINE__, ##__VA_ARGS__);                                     \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);     \
    fflush(stdout);                                                      \
  } while (0)

#define LOG_T(format, ...)                              \
  do {                                                  \
    char buffer[26];                                    \
    POPULATE_TIME_BUFFER(buffer);                       \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__); \
    fflush(stdout);                                     \
  } while (0)

#define LOGG_T(format, ...)                                           \
  do {                                                                \
    char buffer[26];                                                  \
    POPULATE_TIME_BUFFER(buffer);                                     \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::GREEN); \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);               \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);  \
    fflush(stdout);                                                   \
  } while (0)

#define LOGY_T(format, ...)                                            \
  do {                                                                 \
    char buffer[26];                                                   \
    POPULATE_TIME_BUFFER(buffer);                                      \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::YELLOW); \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGB_T(format, ...)                                          \
  do {                                                               \
    char buffer[26];                                                 \
    POPULATE_TIME_BUFFER(buffer);                                    \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BLUE); \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGM_T(format, ...)                                             \
  do {                                                                  \
    char buffer[26];                                                    \
    POPULATE_TIME_BUFFER(buffer);                                       \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::MAGENTA); \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);                 \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);    \
    fflush(stdout);                                                     \
  } while (0)

#define LOGC_T(format, ...)                                          \
  do {                                                               \
    char buffer[26];                                                 \
    POPULATE_TIME_BUFFER(buffer);                                    \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::CYAN); \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#define LOGR_T(format, ...)                                          \
  do {                                                               \
    char buffer[26];                                                 \
    POPULATE_TIME_BUFFER(buffer);                                    \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::RED);  \
    printf("[%s] " format "\n", buffer, ##__VA_ARGS__);              \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE); \
    fflush(stdout);                                                  \
  } while (0)

#endif /* UTILS_TIMEDLOG_H_ */
