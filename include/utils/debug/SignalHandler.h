#ifndef UTILS_SIGNALHANDLER_H_
#define UTILS_SIGNALHANDLER_H_

// System headers
#include <cstdint>
#include <csignal>

// Other libraries header

// Own components headers

// Forward declarations

class SignalHandler {
 public:
  SignalHandler() = delete;

  /** @brief used to install a specific system signal to hander() callback
   * */
  static void installSignal(const int32_t signalNumber);

 private:
  /** @brief callback is performed when the desired signal is received
   * */
  static void segFaultHandler(const int32_t signalNumber);

  /** @brief callback is performed when the desired signal is received
   * */
  static void sigQuitHandler(const int32_t signalNumber);
};

#endif /* UTILS_SIGNALHANDLER_H_ */
