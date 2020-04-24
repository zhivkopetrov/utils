// Corresponding header
#include "utils/include/common/ResourceFileHeader.h"

// C system headers

// C++ system headers

// Other libraries headers

// Own components headers
#include "utils/include/LimitValues.hpp"

std::string ResourceFileHeader::getEngineResHeader() {
  return "# This file is auto-generated. Do not modify it. \n\n"
         "# Resource Builder Tool version 1.0 \n"
         "# Author: Zhivko Petrov\n\n# All static widgets count:\n";
}

std::string ResourceFileHeader::getEngineResHeaderAddition() {
  return "# All dynamic widgets count:\n";
}

std::string ResourceFileHeader::getEngineResDynamicValuesHeader() {
  return "/* This file is auto-generated. Do not modify it. */\n\n"
         "/* Resource Builder Tool version 1.0 */\n"
         "/* Author: Zhivko Petrov */\n\n"
         "/* Dynamic Resources Value Tags:\n";
}

std::string ResourceFileHeader::getEngineFontHeader() {
  return "# This file is auto-generated. Do not modify it. \n\n"
         "# Resource Builder Tool version 1.0 \n"
         "# Author: Zhivko Petrov\n\n# All fonts count:\n";
}

std::string ResourceFileHeader::getEngineSoundHeader() {
  return "# This file is auto-generated. Do not modify it. \n\n"
         "# Resource Builder Tool version 1.0 \n"
         "# Author: Zhivko Petrov\n\n# All music sounds count:\n";
}

std::string ResourceFileHeader::getEngineSoundHeaderAddition() {
  return "# All chunks sounds count:\n";
}

std::string ResourceFileHeader::getEngineCommonGamesHeader() {
  return "# This file is auto-generated. Do not modify it. \n\n"
         "# Resource Builder Tool version 1.0 \n"
         "# Author: Zhivko Petrov\n\n# All common games folders count:\n";
}

std::string ResourceFileHeader::getEngineValueReservedSlot() {
  return std::to_string(INIT_UINT64_VALUE);
}

std::string ResourceFileHeader::getEngineFileSizeHeader() {
  return "# Size of all files in kBytes:\n";
}

std::string ResourceFileHeader::getResourceFileHeader() {
  return "/* This file is auto-generated. Do not modify it. */\n\n"
         "/* Resource Builder Tool version 1.0 */\n"
         "/* Author: Zhivko Petrov */\n\n";
}
