#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

// System headers
#include <cstdarg>
#include <cstdio>
#include <ctime>

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

// function below carry a timestamp in the beginning of the message with format
//"%Y-%m-%d %H:%M:%S"

#define LOGERR_T(format, ...)                                              \
  do {                                                                   \
    time_t timer;                                                        \
    char buffer[26];                                                     \
    time(&timer);                                                        \
    const tm* tm_info = localtime(&timer);                               \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                  \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BOLD_RED); \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__,   \
           __LINE__, ##__VA_ARGS__);                                     \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);     \
    fflush(stdout);                                                      \
  } while (0)

#define LOG_T(format, ...)                                              \
  do {                                                                   \
    time_t timer;                                                        \
    char buffer[26];                                                     \
    time(&timer);                                                        \
    const tm* tm_info = localtime(&timer);                               \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                  \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__,   \
           __LINE__, ##__VA_ARGS__);                                     \
    fflush(stdout);                                                      \
  } while (0)

#define LOGG_T(format, ...)                                            \
  do {                                                                 \
    time_t timer;                                                      \
    char buffer[26];                                                   \
    time(&timer);                                                      \
    const tm* tm_info = localtime(&timer);                             \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::GREEN);  \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__, \
           __LINE__, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGY_T(format, ...)                                            \
  do {                                                                 \
    time_t timer;                                                      \
    char buffer[26];                                                   \
    time(&timer);                                                      \
    const tm* tm_info = localtime(&timer);                             \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::YELLOW); \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__, \
           __LINE__, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGB_T(format, ...)                                            \
  do {                                                                 \
    time_t timer;                                                      \
    char buffer[26];                                                   \
    time(&timer);                                                      \
    const tm* tm_info = localtime(&timer);                             \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::BLUE);   \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__, \
           __LINE__, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGM_T(format, ...)                                             \
  do {                                                                  \
    time_t timer;                                                       \
    char buffer[26];                                                    \
    time(&timer);                                                       \
    const tm* tm_info = localtime(&timer);                              \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                 \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::MAGENTA); \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__,  \
           __LINE__, ##__VA_ARGS__);                                    \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);    \
    fflush(stdout);                                                     \
  } while (0)

#define LOGC_T(format, ...)                                            \
  do {                                                                 \
    time_t timer;                                                      \
    char buffer[26];                                                   \
    time(&timer);                                                      \
    const tm* tm_info = localtime(&timer);                             \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::CYAN);   \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__, \
           __LINE__, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#define LOGR_T(format, ...)                                            \
  do {                                                                 \
    time_t timer;                                                      \
    char buffer[26];                                                   \
    time(&timer);                                                      \
    const tm* tm_info = localtime(&timer);                             \
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);                \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::RED);    \
    printf("[%s] %s(%s:%d): " format "\n", buffer, __func__, __FILE__, \
           __LINE__, ##__VA_ARGS__);                                   \
    LogInternal::setTerminalColor(LogInternal::TerminalColor::NONE);   \
    fflush(stdout);                                                    \
  } while (0)

#endif /* UTILS_LOG_H_ */
