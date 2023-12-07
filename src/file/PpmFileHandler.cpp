// Corresponding header
#include "utils/file/PpmFileHandler.h"

// System headers

// Other libraries headers

// Own components headers
#include "utils/log/Log.h"
#include "utils/data_type/EnumClassUtils.h"

namespace {
size_t readFileSize(std::fstream &fileStream) {
  // point at beginning of file
  fileStream.seekg(0, std::ifstream::beg);
  const std::streampos startPos = fileStream.tellg();

  // Acquire file size
  fileStream.seekg(0, std::ifstream::end);
  return static_cast<size_t>(fileStream.tellg() - startPos);
}
}  // anonymous namespace

ErrorCode PpmFileHandler::writeFile(const std::string &file,
                                    const PpmHeader &header,
                                    const std::vector<Color> &pixels) {
  ErrorCode err = validateWrite(file, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validateWrite() failed for file: %s", file.c_str());
    return err;
  }

  err = openWriteStream(file);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("openWriteStream() failed for file: %s", file.c_str());
    return err;
  }

  if (PpmVersion::P3 == header.version) {
    doWriteP3Format(header, pixels);
  } else {
    doWriteP6Format(header, pixels);
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::readFile(const std::string &file,
                                   PpmHeader &outHeader,
                                   std::vector<Color> &outPixels) {
  size_t payloadByteSize = 0;
  ErrorCode err = validateRead(file, outHeader, payloadByteSize);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validateRead() failed for file: %s", file.c_str());
    return err;
  }

  if (PpmVersion::P3 == outHeader.version) {
    err = doReadP3Format(outHeader, payloadByteSize, outPixels);
  } else {
    err = doReadP6Format(outHeader, payloadByteSize, outPixels);
  }
  if (ErrorCode::SUCCESS != err) {
    LOGERR("doReadP3/P6Format() failed for file: %s", file.c_str());
    return err;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::validateFile(const std::string &file) const {
  const size_t idx = file.rfind(".ppm");
  if (std::string::npos == idx) {
    LOGERR("Error, file: [%s] must end with .ppm extension", file.c_str());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::validateHeader(const PpmHeader &header) const {
  if ((PpmVersion::P3 != header.version) &&
      (PpmVersion::P6 != header.version)) {
    LOGERR(
        "Error, received unsupported PpmVersion: %d. Currently only "
        "P3 and P6 versions are supported",
        getEnumValue(header.version));
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::validateWrite(
    const std::string &file, const PpmHeader &header,
    const std::vector<Color> &pixels) const {
  ErrorCode err = validateFile(file);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validateFile() failed for file: %s", file.c_str());
    return err;
  }

  err = validateHeader(header);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validateHeader() failed for file: %s", file.c_str());
    return err;
  }

  const size_t expectedPixelsCtn =
      static_cast<size_t>(header.imageWidth) * header.imageHeight;
  const size_t providedPixelsCtn = pixels.size();
  if (expectedPixelsCtn != providedPixelsCtn) {
    LOGERR("Error, expectedPixelsCtn/providedPixelsCtn mismatch. %zu vs %zu",
           expectedPixelsCtn, providedPixelsCtn);
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::validateRead(const std::string &file,
                                       PpmHeader &outHeader,
                                       size_t &outPayloadByteSize) {
  ErrorCode err = validateFile(file);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validateFile() failed for file: %s", file.c_str());
    return err;
  }

  err = openReadStream(file);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("openReadStream() failed for file: %s", file.c_str());
    return err;
  }

  outPayloadByteSize = readFileSize(mFileStream);
  // restore pointer to beginning of file
  mFileStream.seekg(0, std::ifstream::beg);

  std::string formatStr;
  mFileStream >> formatStr >> outHeader.imageWidth >> outHeader.imageHeight >>
      outHeader.maxColorComponent;
  if (P3_HEADER_VALUE == formatStr) {
    outHeader.version = PpmVersion::P3;
  } else if (P6_HEADER_VALUE == formatStr) {
    outHeader.version = PpmVersion::P6;
  } else {
    LOGERR(
        "Error, received unsupported PpmVersion: %s. Currently only "
        "P3 and P6 versions are supported",
        formatStr.c_str());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::openWriteStream(const std::string &file) {
  mFileStream.open(file.c_str(), std::ios::out | std::ios::binary);
  if (!mFileStream) {
    LOGERR("Error, file: [%s] could not be created", file.c_str());
    return ErrorCode::FAILURE;
  }

  // stop MSVC wasteful flushing policy on every write
  mFileStream << std::nounitbuf;

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::openReadStream(const std::string &file) {
  mFileStream.open(file.c_str(), std::ios::in | std::ios::binary);
  if (!mFileStream) {
    LOGERR("Error, file: [%s] could not be opened", file.c_str());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

void PpmFileHandler::doWriteP3Format(const PpmHeader &header,
                                     const std::vector<Color> &pixels) {
  mFileStream << P3_HEADER_VALUE << '\n'
              << header.imageWidth << ' ' << header.imageHeight << '\n'
              << header.maxColorComponent << '\n';

  uint32_t pixelColId = 0;
  for (const Color &color : pixels) {
    mFileStream << static_cast<uint32_t>(color.rgba.r) << ' '
                << static_cast<uint32_t>(color.rgba.g) << ' '
                << static_cast<uint32_t>(color.rgba.b) << '\t';
    if (header.imageWidth == pixelColId) {
      pixelColId = 0;
      mFileStream << '\n';
    }
  }
}

void PpmFileHandler::doWriteP6Format(const PpmHeader &header,
                                     const std::vector<Color> &pixels) {
  mFileStream << P6_HEADER_VALUE << '\n'
              << header.imageWidth << ' ' << header.imageHeight << '\n'
              << header.maxColorComponent << '\n';

  for (const Color &color : pixels) {
    mFileStream << static_cast<char>(color.rgba.r)
                << static_cast<char>(color.rgba.g)
                << static_cast<char>(color.rgba.b);
  }
  mFileStream << '\n';
}

ErrorCode PpmFileHandler::doReadP3Format(
    const PpmHeader &header, [[maybe_unused]] size_t payloadByteSize,
    std::vector<Color> &outPixels) {
  const size_t pixelCount =
      static_cast<size_t>(header.imageWidth) * header.imageHeight;
  outPixels.resize(pixelCount, Colors::BLACK);
  size_t pixelId = 0;
  int32_t red{}, green{}, blue{};
  for (Color &pixel : outPixels) {
    if (!(mFileStream >> red >> green >> blue)) {
      LOGERR("Error, expectedPixelsCtn/providedPixelsCtn mismatch. %zu vs %zu",
             pixelCount, pixelId + 1);
      return ErrorCode::FAILURE;
    }
    pixel.rgba.r = static_cast<uint8_t>(red);
    pixel.rgba.g = static_cast<uint8_t>(green);
    pixel.rgba.b = static_cast<uint8_t>(blue);
    ++pixelId;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileHandler::doReadP6Format(const PpmHeader &header,
                                         size_t payloadByteSize,
                                         std::vector<Color> &outPixels) {
  constexpr size_t bytesPerPixel = 3;
  const size_t expectedPixelCount =
      static_cast<size_t>(header.imageWidth) * header.imageHeight;
  const size_t expectedPayloadSize = expectedPixelCount * bytesPerPixel;

  if (expectedPayloadSize > payloadByteSize) {
    LOGERR("Error, expectedPixelsCtn/providedPixelsCtn mismatch. %zu vs %zu",
           expectedPixelCount, payloadByteSize / bytesPerPixel);
    return ErrorCode::FAILURE;
  }

  char stripNewlineChar;
  mFileStream.readsome(&stripNewlineChar, sizeof(stripNewlineChar));

  std::vector<char> rawPayloadData(expectedPayloadSize);
  mFileStream.read(&rawPayloadData.front(), expectedPayloadSize);

  outPixels.reserve(bytesPerPixel);
  for (size_t i = 0; i < expectedPayloadSize; i += bytesPerPixel) {
    outPixels.emplace_back(static_cast<uint8_t>(rawPayloadData[i]),
                           static_cast<uint8_t>(rawPayloadData[i + 1]),
                           static_cast<uint8_t>(rawPayloadData[i + 2]));
  }

  return ErrorCode::SUCCESS;
}