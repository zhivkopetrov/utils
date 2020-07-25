// Corresponding header
#include "utils/debug/SignalHandler.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/debug/StackTrace.hpp"
#include "utils/ErrorCode.h"
#include "utils/Log.h"

void SignalHandler::installSignal(const int32_t signalNumber) {
  switch (signalNumber) {
    case SIGSEGV:
      signal(signalNumber, SignalHandler::segFaultHandler);
      break;
    case SIGQUIT:
      signal(signalNumber, SignalHandler::sigQuitHandler);
      break;
    default:
      LOGERR("Unknown signal installed - %d", signalNumber)
      break;
  }
}

void SignalHandler::segFaultHandler(const int32_t) {
  LOG("Received signal SIGSEGV, Segmentation fault. Printing stack trace:");
  printStacktrace();

  exit(FAILURE);
}

void SignalHandler::sigQuitHandler(const int32_t) {
  printStacktrace();

  LOGR("Program stopped at SIGQUIT")
}
