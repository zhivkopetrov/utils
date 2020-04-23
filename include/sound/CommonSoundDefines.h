#ifndef UTILS_INCLUDE_SOUND_COMMONSOUNDDEFINES_H_
#define UTILS_INCLUDE_SOUND_COMMONSOUNDDEFINES_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers

enum class SoundType : uint8_t { UNKNOWN = 0, MUSIC, CHUNK };

enum class SoundLevel : uint8_t {
  NONE = 0,
  LOW = 32,
  MEDIUM = 64,
  HIGH = 96,
  VERY_HIGH = 128,

  UNKNOWN = 255
};

SoundLevel& operator++(SoundLevel& instance);

#endif /* UTILS_INCLUDE_SOUND_COMMONSOUNDDEFINES_H_ */
