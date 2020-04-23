#ifndef UTILS_INCLUDE_COMMON_DEFINES_RESOURCEDEFINES_H_
#define UTILS_INCLUDE_COMMON_DEFINES_RESOURCEDEFINES_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

namespace ResourceDefines {
enum class FieldType : uint8_t {
  UNKNOWN = 0,
  IMAGE,
  SPRITE,
  SPRITE_MANUAL,
  FONT,
  SOUND
};

enum class SpriteLayout : uint8_t { VERTICAL = 0, HORIZONTAL, MIXED, UNKNOWN };

enum Field {
  TAG = 0,
  TYPE,
  PATH,
  DESCRIPTION,
  POSITION,
  LOAD,
  END_FIELD
};

enum SpriteDataDescriptionIndexes {
  WIDTH_IDX,
  HEIGHT_IDX,
  SPRITE_NUMBER_IDX,
  OFFSET_IDX
};

enum SpriteManualDataDescriptionIndexes {
  IMAGE_X_IDX,
  IMAGE_Y_IDX,
  SPRITE_WIDTH_IDX,
  SPRITE_HEIGHT_IDX
};

enum TextureLoadType { ON_INIT = 0, ON_DEMAND = 1 };
} /* namespace ResourceDefines */

#endif /* UTILS_INCLUDE_COMMON_DEFINES_RESOURCEDEFINES_H_ */
