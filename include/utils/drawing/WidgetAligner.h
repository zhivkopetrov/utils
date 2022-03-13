#ifndef UTILS_WIDGETALIGNER_H
#define UTILS_WIDGETALIGNER_H

// System headers

// Other libraries headers

// Own components headers
#include "utils/drawing/Margin.h"
#include "utils/drawing/Point.h"

// Forward declarations
struct Rectangle;
class Widget;
class ButtonBase;

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
                           const Margin& padding = Margins::ZERO);

  /**
   * @brief Gets aligned X coordinates of a ButtonBase object by a passed
   * in rectangle object (container) and a widget alignment type
   * **/
  static int32_t getAlignedX(const int32_t widgetWidth,
                             const int32_t containerX, const int32_t containerW,
                             const WidgetAlignment alignment,
                             const Margin& padding = Margins::ZERO);

  static int32_t getAlignedY(const int32_t widgetHeight,
                             const int32_t containerY, const int32_t containerH,
                             const WidgetAlignment alignment,
                             const Margin& padding = Margins::ZERO);
};

#endif  // UTILS_WIDGETALIGNER_H
