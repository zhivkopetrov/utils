#ifndef UTILS_INCLUDE_SOUND_COMMONSOUNDSTRUCTS_H_
#define UTILS_INCLUDE_SOUND_COMMONSOUNDSTRUCTS_H_

// C system headers

// C++ system headers
#include <cstdint>

// Other libraries headers

// Own components headers
#include "CommonSoundDefines.h"

#include "common/CommonStructs.h"

// Sound specific data
struct SoundData {
  SoundData() { reset(); }

  // move piecewise constructor - used for emplace_back move semantics
  SoundData(const DataHeader& inputHeader, const SoundType inputSoundType,
            const SoundLevel inputSoundLevel)
      : header(inputHeader),
        soundType(inputSoundType),
        soundLevel(inputSoundLevel) {}

  void reset() {
    header.reset();
    soundType = SoundType::UNKNOWN;
    soundLevel = SoundLevel::UNKNOWN;
  }

  DataHeader header;
  SoundType soundType;
  SoundLevel soundLevel;
};

#endif /* UTILS_INCLUDE_SOUND_COMMONSOUNDSTRUCTS_H_ */
