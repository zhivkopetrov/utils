#ifndef UTILS_INCLUDE_DRAWING_COMMONRESOURCESTRUCTS_H_
#define UTILS_INCLUDE_DRAWING_COMMONRESOURCESTRUCTS_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers
#include "common/CommonStructs.h"
#include "Rectangle.h"

// Resource specific data
struct ResourceData {
  ResourceData() { reset(); }

  // piecewise constructor - used for emplace_back move semantics
  ResourceData(const DataHeader& inputHeader, const Rectangle& inputRect,
               const std::vector<Rectangle>& inputSpriteData,
               const int32_t inputMonitorId, const int32_t inputTextureLoadType,
               const int32_t inputRefCount)
      : header(inputHeader),
        imageRect(inputRect),
        spriteData(inputSpriteData),
        monitorId(inputMonitorId),
        textureLoadType(inputTextureLoadType),
        refCount(inputRefCount) {}

  void reset() {
    header.reset();
    imageRect = Rectangle::ZERO;
    spriteData.clear();
    monitorId = 0;
    textureLoadType = 0;
    refCount = 0;
  }

  DataHeader header;
  Rectangle imageRect;
  std::vector<Rectangle> spriteData;
  int32_t monitorId;
  int32_t textureLoadType;
  int32_t refCount;
};

// Fond specific data
struct FontData {
  FontData() { reset(); }

  // piecewise constructor - used for emplace_back move semantics
  FontData(const DataHeader& inputHeader, const int32_t inputFontSize)
      : header(inputHeader),
        fontSize(inputFontSize) {}

  void reset() {
    header.reset();
    fontSize = 0;
  }

  DataHeader header;
  int32_t fontSize;
};

#endif /* UTILS_INCLUDE_DRAWING_COMMONRESOURCESTRUCTS_H_ */
