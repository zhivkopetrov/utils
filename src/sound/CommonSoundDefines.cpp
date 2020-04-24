// Corresponding header
#include "utils/include/sound/CommonSoundDefines.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers

SoundLevel& operator++(SoundLevel& instance) {
  switch (instance) {
    case SoundLevel::NONE:
      return instance = SoundLevel::LOW;

    case SoundLevel::LOW:
      return instance = SoundLevel::MEDIUM;

    case SoundLevel::MEDIUM:
      return instance = SoundLevel::HIGH;

    case SoundLevel::HIGH:
      return instance = SoundLevel::VERY_HIGH;

    case SoundLevel::VERY_HIGH:
      return instance = SoundLevel::NONE;

    case SoundLevel::UNKNOWN:
      return instance = SoundLevel::UNKNOWN;
  }

  return instance = SoundLevel::UNKNOWN;
}
