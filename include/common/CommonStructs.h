#ifndef UTILS_INCLUDE_COMMON_COMMONSTRUCTS_H_
#define UTILS_INCLUDE_COMMON_COMMONSTRUCTS_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/include/drawing/Rectangle.h"

// Common header for resources/fonts/sounds specific data
struct DataHeader {
  DataHeader() { reset(); }

  void reset() {
    fileSize = 0;
    hashValue = 0;
    path.clear();
  }

  int32_t fileSize;  // in kBytes
  uint64_t hashValue;
  std::string path;
};

// combination of ResourceData + FontData + SoundData
// this struct is used for parsing the individual .rsrc files
// from resourceBuilderTool
struct CombinedData {
  CombinedData() { reset(); }

  void reset() {
    header.reset();
    fontSize = 0;
    textureLoadType = 0;
    soundType.clear();
    soundLevel.clear();
    tagName.clear();
    type.clear();
    imageRect = Rectangle::ZERO;
    spriteData.clear();
  }

  DataHeader header;
  int32_t fontSize;
  int32_t textureLoadType;
  std::string soundType;
  std::string soundLevel;
  std::string tagName;
  std::string type;
  Rectangle imageRect;
  std::vector<Rectangle> spriteData;
};

#endif /* UTILS_INCLUDE_COMMON_COMMONSTRUCTS_H_ */
