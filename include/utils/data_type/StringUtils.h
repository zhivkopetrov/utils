#ifndef UTILS_STRINGUTILS_H_
#define UTILS_STRINGUTILS_H_

// System headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

class StringUtils {
 public:
  StringUtils() = delete;

  /** @brief used to safely extract precise number of integer values
   *         from string a given string.
   *         NOTE: the out std::vector should be empty before calling
   *         the function, because std::vector.emplace_back()
   *         is used internally.
   *         NOTE2: safeStoi() is used internally. If invalid input is
   *         provided -> it will result in error message and "0" data
   *
   *  @param const std::string & data - the string that will be
   *                                                       extracted from
   *  @param const std::string &      - delimiters used to do the
   *                                            tokenization  e.g. " ,?!"
   *  @param std::vector<double>      - the populated output std::vector
   *                                        as a result of the extraction
   *  @param const uint32_t - maximum number of integers wanted from the
   *                        extract action. This argument is optional, but
   *                        if it's provided it will increase performance,
   *                        since std::vector.reserve() will be invoked.
   *
   *  @returns ErrorCode               - error code
   * */
  static ErrorCode extractDoublesFromString(
      const std::string& data, const std::string& delimiters,
      std::vector<double>* outDoubles,
      const uint32_t MAX_NUMBERS = MAX_NUMBERS_INTERNAL);

  /** @brief used to safely extract precise number of integer values
   *         from string a given string.
   *         NOTE: the out std::vector should be empty before calling
   *         the function, because std::vector.emplace_back()
   *         is used internally.
   *         NOTE2: safeStoi() is used internally. If invalid input is
   *         provided -> it will result in error message and "0" data
   *
   *  @param const std::string & data - the string that will be
   *                                                       extracted from
   *  @param const std::string &      - delimiters used to do the
   *                                            tokenization  e.g. " ,?!"
   *  @param std::vector<int32_t>     - the populated output std::vector
   *                                        as a result of the extraction
   *  @param const uint32_t - maximum number of integers wanted from the
   *                        extract action. This argument is optional, but
   *                        if it's provided it will increase performance,
   *                        since std::vector.reserve() will be invoked.
   *
   *  @returns ErrorCode              - error code
   * */
  static ErrorCode extractIntsFromString(
      const std::string& data, const std::string& delimiters,
      std::vector<int32_t>* outIntegers,
      const uint32_t MAX_NUMBERS = MAX_NUMBERS_INTERNAL);

  /** @brief used to tokenize the input into std::string tokens.
   *         NOTE: the out std::vector should be empty before calling
   *         the function, because std::vector.emplace_back()
   *         is used internally.
   *
   *  @param const std::string & data - the string that will be tokenized
   *  @param const std::string &       - delimiters used to do the
   *                                             tokenization e.g. " ,?!"
   *  @param std::vector<int32_t>     - the populated output std::vector
   *                                      as a result of the tokenization
   *  @param const uint32_t - maximum number of tokens wanted from the
   *                        extract action. This argument is optional, but
   *                        if it's provided it will increase performance,
   *                        since std::vector.reserve() will be invoked.
   * */
  static void tokenize(const std::string& data, const std::string& delimiters,
                       std::vector<std::string>* outTokens,
                       const uint32_t MAX_NUMBERS = MAX_NUMBERS_INTERNAL);

  /** @brief used to safely extract integer value
   *                                             from a given std::string.
   *
   *         NOTE: std::stoi() is used internally. If invalid input is
   *         provided -> it will result in error message and "0" data
   *
   *  @param const std::string& data - the string that will be
   *                                                       extracted from
   *
   *  @returns int32_t - parsed integer value
   * */
  static int32_t safeStoi(const std::string& data);

  /** @brief used to safely extract integer value
   *                                             from a given std::string.
   *
   *         NOTE: std::stod() is used internally. If invalid input is
   *         provided -> it will result in error message and "0" data
   *
   *  @param const std::string& data - the string that will be
   *                                                       extracted from
   *
   *  @returns double - parsed double value
   * */
  static double safeStod(const std::string& data);

 private:
    enum InternalDefines : uint32_t {
        MAX_NUMBERS_INTERNAL = 500
    };
};

#endif /* UTILS_STRINGUTILS_H_ */
