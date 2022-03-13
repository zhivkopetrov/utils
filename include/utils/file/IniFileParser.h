#ifndef UTILS_INIFILEPARSER_H_
#define UTILS_INIFILEPARSER_H_

// System headers
#include <string>
#include <string_view>
#include <unordered_map>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

using IniFileSection = std::unordered_map<std::string, std::string>;
using IniFileData = std::unordered_map<std::string, IniFileSection>;

class IniFileParser {
public:
  IniFileParser() = delete;

  static ErrorCode parseFile(std::string_view file, IniFileData &outData);

  static bool getKeyValueInt(const IniFileSection &section,
                             const std::string &identifier, int32_t &outValue);

  static bool getKeyValueFloat(const IniFileSection &section,
                               const std::string &identifier, float &outValue);

  static bool getKeyValueString(const IniFileSection &section,
                                const std::string &identifier,
                                std::string &outValue);

  //for debug purposes
  static void print(const IniFileData &data);
};

#endif /* UTILS_INIFILEPARSER_H_ */
