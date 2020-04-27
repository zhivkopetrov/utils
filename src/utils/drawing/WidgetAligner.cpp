// Corresponding header
#include "utils/drawing/WidgetAligner.h"

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "utils/drawing/Rectangle.h"
#include "utils/LimitValues.hpp"
#include "utils/Log.h"

Point WidgetAligner::getPosition(const int32_t widgetWidth,
                                 const int32_t widgetHeight,
                                 const Rectangle& container,
                                 const WidgetAlignment alignment,
                                 const Margins& padding) {
  const int32_t x =
      getAlignedX(widgetWidth, container.x, container.w, alignment, padding);

  const int32_t y =
      getAlignedY(widgetHeight, container.y, container.h, alignment, padding);

  return Point(x, y);
}

int32_t WidgetAligner::getAlignedX(const int32_t widgetWidth,
                                   const int32_t containerX,
                                   const int32_t containerW,
                                   const WidgetAlignment alignment,
                                   const Margins& padding) {
  const int32_t STARTING_X = containerX + padding.left;

  const int32_t CENTER_STARTING_X = containerX + (containerW - widgetWidth) / 2;

  const int32_t RIGHT_STARTING_X =
      containerX + containerW - (widgetWidth + padding.right);

  switch (alignment) {
    case WidgetAlignment::UPPER_LEFT:
    case WidgetAlignment::CENTER_LEFT:
    case WidgetAlignment::LOWER_LEFT:
      return STARTING_X;

    case WidgetAlignment::UPPER_CENTER:
    case WidgetAlignment::CENTER_CENTER:
    case WidgetAlignment::LOWER_CENTER:
      return CENTER_STARTING_X;

    case WidgetAlignment::UPPER_RIGHT:
    case WidgetAlignment::CENTER_RIGHT:
    case WidgetAlignment::LOWER_RIGHT:
      return RIGHT_STARTING_X;
    default:
      LOGERR("Undefined WidgetAlignment type passed !!!")
  }

  return INIT_INT32_VALUE;
}

int32_t WidgetAligner::getAlignedY(const int32_t widgetHeight,
                                   const int32_t containerY,
                                   const int32_t containerH,
                                   const WidgetAlignment alignment,
                                   const Margins& padding) {
  const int32_t STARTING_Y = containerY + padding.top;

  const int32_t CENTER_STARTING_Y =
      containerY + (containerH - widgetHeight) / 2;

  const int32_t LOWER_STARTING_Y =
      containerY + containerH - (widgetHeight + padding.bottom);

  switch (alignment) {
    case WidgetAlignment::UPPER_LEFT:
    case WidgetAlignment::UPPER_CENTER:
    case WidgetAlignment::UPPER_RIGHT:
      return STARTING_Y;

    case WidgetAlignment::CENTER_LEFT:
    case WidgetAlignment::CENTER_CENTER:
    case WidgetAlignment::CENTER_RIGHT:
      return CENTER_STARTING_Y;

    case WidgetAlignment::LOWER_LEFT:
    case WidgetAlignment::LOWER_CENTER:
    case WidgetAlignment::LOWER_RIGHT:
      return LOWER_STARTING_Y;
    default:
      LOGERR("Undefined WidgetAlignment type passed !!!")
  }

  return INIT_INT32_VALUE;
}
