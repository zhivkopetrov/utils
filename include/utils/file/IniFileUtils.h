#ifndef UTILS_INIFILEUTILS_H_
#define UTILS_INIFILEUTILS_H_

// System headers
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

using IniFileSection = std::unordered_map<std::string, std::string>;
using IniFileData = std::unordered_map<std::string, IniFileSection>;

class IniFileUtils {
public:
  IniFileUtils() = delete;

  static ErrorCode parseFile(std::string_view file, IniFileData &outData);

  //will override filePath on each call
  static ErrorCode serializeFile(
    const std::string& filePath, const IniFileData &data);

  static bool getKeyValueInt(const IniFileSection &section,
                             const std::string &identifier, int32_t &outValue);

  static bool getKeyValueUint(const IniFileSection &section,
                              const std::string &identifier, uint32_t &outValue);

  static bool getKeyValueFloat(const IniFileSection &section,
                               const std::string &identifier, float &outValue);

  static bool getKeyValueString(const IniFileSection &section,
                                const std::string &identifier,
                                std::string &outValue);

  //for debug purposes
  static void print(const IniFileData &data);
};

#endif /* UTILS_INIFILEUTILS_H_ */
