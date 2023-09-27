#ifndef UTILS_PPMFILEHANDLER_H_
#define UTILS_PPMFILEHANDLER_H_

// System headers
#include <fstream>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"
#include "utils/drawing/Color.h"
#include "utils/file/PpmDefines.h"

// Forward declarations

class PpmFileHandler {
 public:
  ErrorCode writeFile(const std::string &file, const PpmHeader &header,
                      const std::vector<Color> &pixels);

  ErrorCode readFile(const std::string &file, PpmHeader &outHeader,
                     std::vector<Color> &outPixels);

 private:
  ErrorCode validateWrite(const std::string &file, const PpmHeader &header,
                          const std::vector<Color> &pixels) const;
  ErrorCode validateRead(const std::string &file, PpmHeader &outHeader,
                         size_t &outPayloadByteSize);

  ErrorCode validateFile(const std::string &file) const;
  ErrorCode validateHeader(const PpmHeader &header) const;

  ErrorCode openWriteStream(const std::string &file);
  ErrorCode openReadStream(const std::string &file);

  void doWriteP3Format(const PpmHeader &header,
                       const std::vector<Color> &pixels);
  void doWriteP6Format(const PpmHeader &header,
                       const std::vector<Color> &pixels);

  ErrorCode doReadP3Format(const PpmHeader &header, size_t payloadByteSize,
                           std::vector<Color> &outPixels);
  ErrorCode doReadP6Format(const PpmHeader &header, size_t payloadByteSize,
                           std::vector<Color> &outPixels);

  std::fstream mFileStream;
};

#endif /* UTILS_PPMFILEHANDLER_H_ */
