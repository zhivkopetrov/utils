// Corresponding header
#include "utils/data_type/StringUtils.h"

// C system headers

// C++ system headers
#include <cctype>
#include <sstream>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

int32_t StringUtils::extractIntsFromString(const std::string& data,
                                           const std::string& delimiters,
                                           std::vector<int32_t>* outIntegers,
                                           const uint32_t MAX_NUMBERS) {
  std::vector<std::string> tokens;

  // if maximum number is provided do reserve for increase in performance
  if (MAX_NUMBERS_INTERNAL != MAX_NUMBERS) {
    outIntegers->reserve(MAX_NUMBERS);

    // do the tokenization with known number of output tokens
    tokenize(data, delimiters, &tokens, MAX_NUMBERS);
  } else {
    // do the tokenization with unknown number of output tokens
    tokenize(data, delimiters, &tokens);
  }

  if (0 == tokens.size()) {
    LOGERR("Error, empty string data provided -> no tokenize is possible");
    return FAILURE;
  }

  const uint32_t TOKENS_SIZE = static_cast<uint32_t>(tokens.size());

  // if maximum number is not provided -> emplace_back all the tokens
  if (MAX_NUMBERS_INTERNAL != MAX_NUMBERS) {
    for (uint32_t i = 0; i < TOKENS_SIZE; ++i) {
      outIntegers->emplace_back(safeStoi(tokens[i]));
    }
  }
  // maximum number is provided -> tokens can be more that the
  // provided maximum value -> check for such case
  else {
    for (uint32_t i = 0; i < MAX_NUMBERS && i < TOKENS_SIZE; ++i) {
      outIntegers->emplace_back(safeStoi(tokens[i]));
    }
  }

  return SUCCESS;
}

int32_t StringUtils::extractDoublesFromString(const std::string& data,
                                              const std::string& delimiters,
                                              std::vector<double>* outDoubles,
                                              const uint32_t MAX_NUMBERS) {
  std::vector<std::string> tokens;

  // if maximum number is provided do reserve for increase in performance
  if (MAX_NUMBERS_INTERNAL != MAX_NUMBERS) {
    outDoubles->reserve(MAX_NUMBERS);

    // do the tokenization with known number of output tokens
    tokenize(data, delimiters, &tokens, MAX_NUMBERS);
  } else {
    // do the tokenization with unknown number of output tokens
    tokenize(data, delimiters, &tokens);
  }

  if (0 == tokens.size()) {
    LOGERR("Error, empty string data provided -> no tokenize is possible");
    return FAILURE;
  }

  const uint32_t TOKENS_SIZE = static_cast<uint32_t>(tokens.size());

  // if maximum number is not provided -> emplace_back all the tokens
  if (MAX_NUMBERS_INTERNAL != MAX_NUMBERS) {
    for (uint32_t i = 0; i < TOKENS_SIZE; ++i) {
      outDoubles->emplace_back(safeStod(tokens[i]));
    }
  }
  // maximum number is provided -> tokens can be more that the
  // provided maximum value -> check for such case
  else {
    for (uint32_t i = 0; i < MAX_NUMBERS && i < TOKENS_SIZE; ++i) {
      outDoubles->emplace_back(safeStod(tokens[i]));
    }
  }

  return SUCCESS;
}

void StringUtils::tokenize(const std::string& data,
                           const std::string& delimiters,
                           std::vector<std::string>* outTokens,
                           const uint32_t MAX_NUMBERS) {
  // if maximum number is provided do reserve for increase in performance
  if (MAX_NUMBERS_INTERNAL != MAX_NUMBERS) {
    outTokens->reserve(MAX_NUMBERS);
  }

  uint64_t prev = 0;
  uint64_t pos = 0;

  while (std::string::npos != (pos = data.find_first_of(delimiters, prev))) {
    if (pos > prev) {
      outTokens->emplace_back(data.substr(prev, pos - prev));
    }

    prev = pos + 1;
  }

  if (prev < data.size()) {
    outTokens->emplace_back(data.substr(prev, std::string::npos));
  }
}

int32_t StringUtils::safeStoi(const std::string& data) {
  const uint32_t DATA_SIZE = static_cast<uint32_t>(data.size());

  // check is string is not empty
  if (DATA_SIZE > 0) {
    if (!isdigit(data[0])) {
      // check if it starts with a sign symbol
      // if yes -> check if it has any digits behind it
      if (!(DATA_SIZE > 1 && (('-' == data[0]) || ('+' == data[0])))) {
        LOGERR("Warning, data: [%s] is not in numerical format -> stoi will "
               "return result 0: %d", data.c_str(), 0);
        return 0;
      }
    }
  }

  for (uint32_t i = 1; i < DATA_SIZE; ++i) {
    if (!isdigit(data[i])) {
      LOGERR(
          "Warning, data: [%s] is not in numerical format ->"
          "stoi will return result 0: %d",
          data.c_str(), 0);

      return 0;
    }
  }

  return std::stoi(data);
}

double StringUtils::safeStod(const std::string& data) {
  const uint32_t DATA_SIZE = static_cast<uint32_t>(data.size());

  // check is string is not empty
  if (DATA_SIZE > 0) {
    if (!isdigit(data[0])) {
      // check if it starts with a sign symbol
      // if yes -> check if it has any digits behind it
      if (!(DATA_SIZE > 1 && (('-' == data[0]) || ('+' == data[0])))) {
        LOGERR("Warning, data: [%s] is not in numerical format -> stod will "
               "return result 0: %d", data.c_str(), 0);
        return 0;
      }
    }
  }

  bool isDecimalDigitFound = false;

  for (uint32_t i = 1; i < DATA_SIZE; ++i) {
    if (!isdigit(data[i])) {
      if (!isDecimalDigitFound)  // allow only 1 decimal character
      {
        isDecimalDigitFound = true;
        continue;
      }

      LOGERR("Warning, data: [%s] is not in numerical format -> stod will "
             "return result 0: %d", data.c_str(), 0);
      return 0;
    }
  }

  return std::stod(data);
}
