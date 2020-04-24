#ifndef UTILS_INCLUDE_DRAWING_WIDGETALIGNER_H
#define UTILS_INCLUDE_DRAWING_WIDGETALIGNER_H

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/include/drawing/Margins.h"
#include "utils/include/drawing/Point.h"

// Forward declarations
class Widget;
class ButtonBase;
class Rectangle;

enum class WidgetAlignment {
  UPPER_LEFT = 0,
  UPPER_CENTER,
  UPPER_RIGHT,
  CENTER_LEFT,
  CENTER_CENTER,
  CENTER_RIGHT,
  LOWER_LEFT,
  LOWER_CENTER,
  LOWER_RIGHT
};

class WidgetAligner {
 public:
  // Disallow creating an instance of this object
  WidgetAligner() = delete;

  /**
   * @brief Aligns a widget by a passed in rectangle object (container)
   * and a widget alignment type
   * **/
  static Point getPosition(const int32_t widgetWidth,
                           const int32_t widgetHeight,
                           const Rectangle& container,
                           const WidgetAlignment alignment,
                           const Margins& padding = Margins::ZERO);

  /**
   * @brief Gets aligned X coordinates of a ButtonBase object by a passed
   * in rectangle object (container) and a widget alignment type
   * **/
  static int32_t getAlignedX(const int32_t widgetWidth,
                             const int32_t containerX, const int32_t containerW,
                             const WidgetAlignment alignment,
                             const Margins& padding = Margins::ZERO);

  static int32_t getAlignedY(const int32_t widgetHeight,
                             const int32_t containerY, const int32_t containerH,
                             const WidgetAlignment alignment,
                             const Margins& padding = Margins::ZERO);
};

#endif  // UTILS_INCLUDE_DRAWING_WIDGETALIGNER_H
