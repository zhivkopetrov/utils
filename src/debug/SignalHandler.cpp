// Corresponding header
#include "utils/debug/SignalHandler.h"

// System headers
#include <cstdlib>

// Other libraries headers

// Own components headers
#include "utils/debug/StackTrace.h"
#include "utils/ErrorCode.h"
#include "utils/log/Log.h"

void SignalHandler::installSignal(const int32_t signalNumber) {
  switch (signalNumber) {
    case SIGSEGV:
      signal(signalNumber, SignalHandler::segFaultHandler);
      break;
#if defined(_WIN32) || defined(_WIN64)
    case SIGBREAK:
#else
    case SIGQUIT:
#endif
      signal(signalNumber, SignalHandler::sigQuitHandler);
      break;
    default:
      LOGERR("Unknown signal installed - %d", signalNumber);
      break;
  }
}

void SignalHandler::segFaultHandler(const int32_t) {
  LOG("Received signal SIGSEGV, Segmentation fault. Printing stack trace:");
  printStacktrace();

  exit(EXIT_FAILURE);
}

void SignalHandler::sigQuitHandler(const int32_t) {
  printStacktrace();

  LOGR("Program stopped at SIGQUIT");
}
