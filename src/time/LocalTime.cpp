// Corresponding header
#include "utils/time/LocalTime.h"

// System headers
#if not defined(__linux__) && not defined(_MSC_VER)
#include <mutex>
#endif

// Other libraries headers

// Own components headers

std::tm localtime_secure(std::time_t timer) {
    std::tm bt {};
#if defined(__linux__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    bt = *std::localtime(&timer);
#endif
    return bt;
}