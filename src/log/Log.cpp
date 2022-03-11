// Corresponding header
#include "utils/Log.h"

// System headers
#if defined _WIN32
#include <windows.h>
#endif

// Other libraries headers

// Own components headers
#include "utils/data_type/EnumClassUtils.h"

#if defined __linux__

#define COLOR_NONE "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BOLD "\033[1m "

#elif defined _WIN32

#define COLOR_NONE 7
#define COLOR_RED 4
#define COLOR_GREEN 2
#define COLOR_BLUE 1
#define COLOR_YELLOW 6
#define COLOR_MAGENTA 5
#define COLOR_CYAN 3
#define COLOR_RED_BOLD 12

#else
  //unsupported OS
#endif

//const int32_t bold red 12 windows;

namespace LogInternal {
void setTerminalColor([[maybe_unused]]TerminalColor color) {
#if defined __linux__

  switch (color) {
  case TerminalColor::NONE:
    printf(COLOR_NONE);
    break;
  case TerminalColor::RED:
    printf(COLOR_RED);
    break;
  case TerminalColor::GREEN:
    printf(COLOR_GREEN);
    break;
  case TerminalColor::BLUE:
    printf(COLOR_BLUE);
    break;
  case TerminalColor::YELLOW:
    printf(COLOR_YELLOW);
    break;
  case TerminalColor::MAGENTA:
    printf(COLOR_MAGENTA);
    break;
  case TerminalColor::CYAN:
    printf(COLOR_CYAN);
    break;
  case TerminalColor::BOLD_RED:
    printf(COLOR_BOLD COLOR_RED);
    break;
  default:
    printf("Error, received unsupported TerminalColor: %d\n",
        getEnumValue(color));
    break;
  }

#elif defined _WIN32
  WORD colorIdx = 0;
  switch (color) {
  case TerminalColor::NONE:
    colorIdx = COLOR_NONE;
    break;
  case TerminalColor::RED:
    colorIdx = COLOR_RED;
    break;
  case TerminalColor::GREEN:
    colorIdx = COLOR_GREEN;
    break;
  case TerminalColor::BLUE:
    colorIdx = COLOR_BLUE;
    break;
  case TerminalColor::YELLOW:
    colorIdx = COLOR_YELLOW;
    break;
  case TerminalColor::MAGENTA:
    colorIdx = COLOR_MAGENTA;
    break;
  case TerminalColor::CYAN:
    colorIdx = COLOR_CYAN;
    break;
  case TerminalColor::BOLD_RED:
    colorIdx = COLOR_RED_BOLD;
    break;
  default:
    printf("Error, received unsupported TerminalColor: %d\n",
        getEnumValue(color));
    break;
  }

  const auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consoleHandle, colorIdx);
#else
  //unsupported OS
#endif
}

} //namespace LogInternal
