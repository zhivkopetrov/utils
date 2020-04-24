// Corresponding header
#include "utils/include/resourceloader/ResourceLoader.h"

// C system headers

// C++ system headers
#include <cstring>
#include <sstream>

// Other libraries headers

// Own components headers
#include "utils/include/common/CommonStructs.h"
#include "utils/include/common/ResourceFileHeader.h"
#include "utils/include/datatype/StringUtils.h"
#include "utils/include/drawing/CommonResourceStructs.h"
#include "utils/include/sound/CommonSoundStructs.h"
#include "utils/include/Log.h"

ResourceLoader::ResourceLoader(const std::string& projectName)
    : _RESOURCES_BIN_NAME("resources.bin"),
      _FONTS_BIN_NAME("fonts.bin"),
      _SOUNDS_BIN_NAME("sounds.bin"),
      _PROJECT_NAME(projectName) {}

ResourceLoader::~ResourceLoader() { deinit(); }

int32_t ResourceLoader::init(const std::string &projectFolderName,
                             ResourceLoaderCfg* outCfg) {
  _projectFolder = projectFolderName + "/";

  if (EXIT_SUCCESS != openSourceStreams()) {
    LOGERR("Error in ResourceLoader::openSourceStream() -> Terminating...");

    return EXIT_FAILURE;
  }

  if (EXIT_SUCCESS != readEngineBinHeaders(outCfg)) {
    LOGERR("Error in readEngineBinHeaders() -> Terminating ...");

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void ResourceLoader::deinit() { closeSourceStreams(); }

int32_t ResourceLoader::openSourceStreams() {
  int32_t err = EXIT_SUCCESS;

  const std::string absoluteFilePath = __FILE__;

  // use rfind, because we are closer to the end
  const uint64_t currDirPos = absoluteFilePath.rfind(_projectFolder);

  std::string resFile = "";
  std::string fontFile = "";
  std::string soundFile = "";

  if (std::string::npos != currDirPos) {
    const std::string projectFilePath =
        absoluteFilePath.substr(0, currDirPos + _projectFolder.size())
            .append("build/");

    resFile = projectFilePath;
    resFile.append(_PROJECT_NAME)
        .append("/resources/")
        .append(_RESOURCES_BIN_NAME);

    fontFile = projectFilePath;
    fontFile.append(_PROJECT_NAME)
        .append("/resources/")
        .append(_FONTS_BIN_NAME);

    soundFile = projectFilePath;
    soundFile.append(_PROJECT_NAME)
        .append("/resources/")
        .append(_SOUNDS_BIN_NAME);
  } else {
    LOGERR("Error, Engine folder could not be found -> Terminating...");

    err = EXIT_FAILURE;
  }

  if (EXIT_SUCCESS == err) {
    _resSourceStream.open(resFile.c_str(),
                          std::ifstream::in | std::ifstream::binary);

    if (!_resSourceStream) {
      LOGERR(
          "Error, could not open ifstream for fileName: %s, "
          "reason: %s",
          resFile.c_str(), strerror(errno));

      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    _fontsSourceStream.open(fontFile.c_str(),
                            std::ifstream::in | std::ifstream::binary);

    if (!_fontsSourceStream) {
      LOGERR(
          "Error, could not open ifstream for fileName: %s,"
          " reason: %s",
          fontFile.c_str(), strerror(errno));

      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    _soundsSourceStream.open(soundFile.c_str(),
                             std::ifstream::in | std::ifstream::binary);

    if (!_soundsSourceStream) {
      LOGERR(
          "Error, could not open ifstream for fileName: %s,"
          " reason: %s",
          soundFile.c_str(), strerror(errno));

      err = EXIT_FAILURE;
    }
  }

  if (EXIT_FAILURE == err) {
    LOGC(
        "Developer hint: Run the resourcebuilder tool in project/build "
        "directory and make before starting engine");
  }

  return err;
}

int32_t ResourceLoader::readEngineBinHeaders(ResourceLoaderCfg* outCfg) {
  int32_t err = EXIT_SUCCESS;

  if (EXIT_SUCCESS != readResourceBinHeader(&outCfg->staticWidgetsCount,
                                            &outCfg->dynamicWidgetsCount,
                                            &outCfg->widgetsFileSize)) {
    LOGERR("Error in readResourceBinHeader()");

    err = EXIT_FAILURE;
  }

  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS !=
        readFontBinHeader(&outCfg->fontsCount, &outCfg->fontsFileSize)) {
      LOGERR("Error in readFontBinHeader()");

      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    if (EXIT_SUCCESS != readSoundBinHeader(&outCfg->musicsCount,
                                           &outCfg->chunksCount,
                                           &outCfg->soundsFileSize)) {
      LOGERR("Error in readSoundBinHeader()");

      err = EXIT_FAILURE;
    }
  }

  return err;
}

int32_t ResourceLoader::readResourceBinHeader(uint64_t* outStaticWidgetsSize,
                                              uint64_t* outDynamicWidgetsSize,
                                              int32_t* outWidgetFileSize) {
  int32_t err = EXIT_SUCCESS;

  const uint64_t RES_HEADER_SIZE =
      ResourceFileHeader::getEngineResHeader().size();
  const uint64_t ENGINE_RESERVED_SLOT_SIZE =
      ResourceFileHeader::getEngineValueReservedSlot().size();
  const uint64_t RES_HEADER_ADDITION_SIZE =
      ResourceFileHeader::getEngineResHeaderAddition().size();

  // move the file pointer to the proper place
  _resSourceStream.seekg(RES_HEADER_SIZE, std::ifstream::beg);

  std::string line = "";
  if (!std::getline(_resSourceStream, line)) {
    LOGERR("Internal error, Could not parse widgetsCount");

    err = EXIT_FAILURE;
  } else {
    const int32_t PARSED_ARGS =
        sscanf(line.c_str(), "%lu", outStaticWidgetsSize);
    if (1 != PARSED_ARGS) {
      LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
             PARSED_ARGS);

      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    const uint64_t OFFSET = RES_HEADER_SIZE + ENGINE_RESERVED_SLOT_SIZE +
                            RES_HEADER_ADDITION_SIZE +
                            2;  //+2 for the 2 newline characters

    // move the file pointer to the proper place
    _resSourceStream.seekg(OFFSET, std::ifstream::beg);

    if (!std::getline(_resSourceStream, line)) {
      LOGERR("Internal error, Could not parse widgetsCount");

      err = EXIT_FAILURE;
    } else {
      const int32_t PARSED_ARGS =
          sscanf(line.c_str(), "%lu", outDynamicWidgetsSize);
      if (1 != PARSED_ARGS) {
        LOGERR(
            "Internal error, sscanf parsed %d arguments "
            "instead of 1",
            PARSED_ARGS);

        err = EXIT_FAILURE;
      }
    }
  }

  if (EXIT_SUCCESS == err) {
    // 3, because we expect 1 newline + 1 line of resource file size header
    // 3th line is the actual data we want to parse with sscanf
    for (int32_t i = 0; i < 3; ++i) {
      if (!std::getline(_resSourceStream, line)) {
        LOGERR("Internal error, not enough data");

        err = EXIT_FAILURE;
        break;
      }
    }
  }

  if (EXIT_SUCCESS == err) {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%d", outWidgetFileSize);
    if (1 != PARSED_ARGS) {
      LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
             PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  return err;
}

int32_t ResourceLoader::readFontBinHeader(uint64_t* outFontsSize,
                                          int32_t* outFontsFileSize) {
  int32_t err = EXIT_SUCCESS;

  // move the file pointer to the proper place
  _fontsSourceStream.seekg(ResourceFileHeader::getEngineFontHeader().size(),
                           std::ifstream::beg);
  std::string line = "";
  if (!std::getline(_fontsSourceStream, line)) {
    LOGERR("Internal error, Could not parse fontsCount");
    err = EXIT_FAILURE;
  } else {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%lu", outFontsSize);
    if (1 != PARSED_ARGS) {
      LOGERR(
          "Internal error, sscanf parsed %d arguments "
          "instead of 1",
          PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    // 3, because we expect 1 newline + 1 line of fonts file size header
    // 3th line is the actual data we want to parse with sscanf
    for (int32_t i = 0; i < 3; ++i) {
      if (!std::getline(_fontsSourceStream, line)) {
        LOGERR("Internal error, not enough data");

        err = EXIT_FAILURE;
        break;
      }
    }
  }

  if (EXIT_SUCCESS == err) {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%d", outFontsFileSize);
    if (1 != PARSED_ARGS) {
      LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
             PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  return err;
}

int32_t ResourceLoader::readSoundBinHeader(uint64_t* outMusicsSize,
                                           uint64_t* outChunksSize,
                                           int32_t* outSoundsFileSize) {
  int32_t err = EXIT_SUCCESS;

  // move the file pointer to the proper place
  _soundsSourceStream.seekg(ResourceFileHeader::getEngineSoundHeader().size(),
                            std::ifstream::beg);

  std::string line = "";
  if (!std::getline(_soundsSourceStream, line)) {
    LOGERR("Internal error, Could not parse soundsCount");
    err = EXIT_FAILURE;
  } else {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%lu", outMusicsSize);
    if (1 != PARSED_ARGS) {
      LOGERR(
          "Internal error, sscanf parsed %d arguments "
          "instead of 1",
          PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    // 3, because we expect 1 newline + 1 line of file sound addition header
    // 3th line is the actual data we want to parse with sscanf
    for (int32_t i = 0; i < 3; ++i) {
      if (!std::getline(_soundsSourceStream, line)) {
        LOGERR("Internal error, not enough data");

        err = EXIT_FAILURE;
        break;
      }
    }
  }

  if (EXIT_SUCCESS == err) {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%lu", outChunksSize);
    if (1 != PARSED_ARGS) {
      LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
             PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  if (EXIT_SUCCESS == err) {
    // 3, because we expect 1 newline + 1 line of sound file size header
    // 3th line is the actual data we want to parse with sscanf
    for (int32_t i = 0; i < 3; ++i) {
      if (!std::getline(_soundsSourceStream, line)) {
        LOGERR("Internal error, not enough data");

        err = EXIT_FAILURE;
        break;
      }
    }
  }

  if (EXIT_SUCCESS == err) {
    const int32_t PARSED_ARGS = sscanf(line.c_str(), "%d", outSoundsFileSize);
    if (1 != PARSED_ARGS) {
      LOGERR("Internal error, sscanf parsed %d arguments instead of 1",
             PARSED_ARGS);
      err = EXIT_FAILURE;
    }
  }

  return err;
}

void ResourceLoader::closeSourceStreams() {
  // close the stream and reset stream flags
  _resSourceStream.close();
  _resSourceStream.clear();

  // close the stream and reset stream flags
  _fontsSourceStream.close();
  _fontsSourceStream.clear();

  // close the stream and reset stream flags
  _soundsSourceStream.close();
  _soundsSourceStream.clear();
}

bool ResourceLoader::readChunkHeaderInternal(
    const ResourceDefines::FieldType fieldType, DataHeader* outData) {
  const int32_t HEADER_SIZE = 3;
  std::string lines[HEADER_SIZE];

  std::ifstream* currStream = nullptr;
  if (ResourceDefines::FieldType::FONT == fieldType) {
    currStream = &_fontsSourceStream;
  } else if (ResourceDefines::FieldType::SOUND == fieldType) {
    currStream = &_soundsSourceStream;
  } else  // FieldType::IMAGE == fieldType || FieldType::SPRITE == fieldType
  {
    currStream = &_resSourceStream;
  }

  // there should be 1 empty newline before each widget internal information
  if (!std::getline(*currStream, lines[0]) || lines[0] != "") {
    return false;
  }

  for (int32_t i = 0; i < HEADER_SIZE; ++i) {
    if (!std::getline(*currStream, lines[i])) {
      return false;
    }
  }

  std::stringstream str(lines[0]);
  str >> std::hex >> outData->hashValue;

  outData->path = lines[1];

  outData->fileSize = StringUtils::safeStoi(lines[2]);

  return true;
}

bool ResourceLoader::readResourceChunk(ResourceData* outData) {
  // for now it doesn't matter if we use FieldType::IMAGE or FieldType::SPRITE,
  // because they both have the same headers
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::SPRITE,
                               &outData->header)) {
    return false;
  }

  const int32_t RES_SPECIFIC_SIZE = 4;
  std::string lines[RES_SPECIFIC_SIZE];

  for (int32_t i = 0; i < RES_SPECIFIC_SIZE; ++i) {
    if (!std::getline(_resSourceStream, lines[i])) {
      return false;
    }
  }

  outData->monitorId = StringUtils::safeStoi(lines[0]);
  outData->textureLoadType = StringUtils::safeStoi(lines[1]);

  std::vector<int32_t> coordsData;
  if (EXIT_SUCCESS !=
      StringUtils::extractIntsFromString(lines[2], " ", &coordsData, 4)) {
    LOGERR("Internal error, not valid coordsData");
    return false;
  }

  outData->imageRect.x = coordsData[0];
  outData->imageRect.y = coordsData[1];
  outData->imageRect.w = coordsData[2];
  outData->imageRect.h = coordsData[3];

  const int32_t SPRITE_COUNT = StringUtils::safeStoi(lines[3]);

  outData->spriteData.reserve(SPRITE_COUNT);

  std::vector<int32_t> spriteData;
  for (int32_t i = 0; i < SPRITE_COUNT; ++i) {
    // reuse lines[0] string. don't need to create separate one
    if (!std::getline(_resSourceStream, lines[0])) {
      return false;
    }

    if (EXIT_SUCCESS !=
        StringUtils::extractIntsFromString(lines[0], " ", &spriteData, 4)) {
      LOGERR("Internal error, not valid sprite data");
      return false;
    }

    outData->spriteData.emplace_back(spriteData[0],   // x
                                     spriteData[1],   // y
                                     spriteData[2],   // w
                                     spriteData[3]);  // h

    // clear vector so we can reuse it
    spriteData.clear();
  }

  return true;
}

bool ResourceLoader::readFontChunk(FontData* outData) {
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::FONT,
                               &outData->header)) {
    return false;
  }

  std::string singleLine = "";
  if (!std::getline(_fontsSourceStream, singleLine)) {
    return false;
  }

  outData->fontSize = StringUtils::safeStoi(singleLine);

  return true;
}

bool ResourceLoader::readSoundChunk(SoundData* outData) {
  if (!readChunkHeaderInternal(ResourceDefines::FieldType::SOUND,
                               &outData->header)) {
    return false;
  }

  const int32_t SOUND_SPECIFIC_SIZE = 2;
  std::string lines[SOUND_SPECIFIC_SIZE];

  for (int32_t i = 0; i < SOUND_SPECIFIC_SIZE; ++i) {
    if (!std::getline(_soundsSourceStream, lines[i])) {
      return false;
    }
  }

  if ("chunk" == lines[0]) {
    outData->soundType = SoundType::CHUNK;
  } else if ("music" == lines[0]) {
    outData->soundType = SoundType::MUSIC;
  } else {
    LOGERR(
        "Error wrong description in file: %s, with tag: %s. Second "
        "argument must be 'music' or 'chunk'",
        _SOUNDS_BIN_NAME.c_str(), outData->header.path.c_str());

    outData->soundType = SoundType::UNKNOWN;
    return false;
  }

  if ("low" == lines[1]) {
    outData->soundLevel = SoundLevel::LOW;
  } else if ("medium" == lines[1]) {
    outData->soundLevel = SoundLevel::MEDIUM;
  } else if ("high" == lines[1]) {
    outData->soundLevel = SoundLevel::HIGH;
  } else if ("very_high" == lines[1]) {
    outData->soundLevel = SoundLevel::VERY_HIGH;
  } else {
    LOGERR(
        "Error wrong description in file: %s, with tag: %s. "
        "Third argument must be 'low', 'medium', 'high' or 'very_high'",
        _SOUNDS_BIN_NAME.c_str(), outData->header.path.c_str());

    outData->soundLevel = SoundLevel::UNKNOWN;
    return false;
  }

  return true;
}
