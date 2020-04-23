#ifndef UTILS_INCLUDE_RESOURCELOADER_RESOURCELOADER_H_
#define UTILS_INCLUDE_RESOURCELOADER_RESOURCELOADER_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <fstream>
#include <string>

// Other libraries headers

// Own components headers
#include "common/defines/ResourceDefines.h"

// Forward declarations
struct ResourceData;
struct FontData;
struct SoundData;
struct DataHeader;
enum class FieldType : uint8_t;

/** @brief used for containing all resources/fonts/sounds listed in
 *         _RESOURCES_BIN_NAME, _FONTS_BIN_NAME and _SOUNDS_BIN_NAME at
 *         project start up and set the total count of widgets/fonts/sounds.
 *
 *  @param uint64_t * - total widgets count
 *  @param uint64_t * - total fonts count
 *  @param uint64_t * - total musics count
 *  @param uint64_t * - total sound chunks count
 *  @param int32_t *  - total widgets file size
 *  @param int32_t *  - total fonts file size
 *  @param int32_t *  - total sounds file size
 *  */
struct ResourceLoaderCfg {
  ResourceLoaderCfg() { reset(); }

  void reset() {
    staticWidgetsCount = 0;
    dynamicWidgetsCount = 0;
    fontsCount = 0;
    musicsCount = 0;
    chunksCount = 0;
    widgetsFileSize = 0;
    fontsFileSize = 0;
    soundsFileSize = 0;
  }

  uint64_t staticWidgetsCount;
  uint64_t dynamicWidgetsCount;
  uint64_t fontsCount;
  uint64_t musicsCount;
  uint64_t chunksCount;
  int32_t widgetsFileSize;
  int32_t fontsFileSize;
  int32_t soundsFileSize;
};

class ResourceLoader {
 public:
  ResourceLoader() = delete;

  explicit ResourceLoader(const std::string& projectName);
  ~ResourceLoader();

  /** @brief used to load and populate the ResourceLoaderCfg
   *
   *  @returns int32_t - error code
   * */
  int32_t init(const std::string &projectFolderName, ResourceLoaderCfg* outCfg);

  /** @brief used to deinitialize the ResourceLoader instance
   * */
  void deinit();

  /** @brief used to parse single resource from _RESOURCES_BIN_NAME
   *
   *  @param ResourceData * - fully parsed ResourceData chunk
   *
   *  @return bool          - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                _RESOURCES_BIN_NAME.eof() is reached.
   * */
  bool readResourceChunk(ResourceData* outData);

  /** @brief used to parse single resource from _FONTS_BIN_NAME
   *
   *  @param ResourceData* - fully parsed FontData chunk
   *
   *  @return bool - successful read or not
   *                 NOTE: unsuccessful read means
   *                                    _FONTS_BIN_NAME.eof() is reached.
   * */
  bool readFontChunk(FontData* outData);

  /** @brief used to parse single resource from _SOUNDS_BIN_NAME
   *
   *  @param ResourceData * - fully parsed SoundData chunk
   *
   *  @return bool          - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                    _SOUNDS_BIN_NAME.eof() is reached.
   * */
  bool readSoundChunk(SoundData* outData);

 private:
  /** @brief used to open file streams for
   *            _RESOURCES_BIN_NAME, _FONTS_BIN_NAME and _SOUNDS_BIN_NAME
   *
   *  @returns int32_t - error code
   * */
  int32_t openSourceStreams();

  /** @brief used to close file streams for
   *            _RESOURCES_BIN_NAME, _FONTS_BIN_NAME and _SOUNDS_BIN_NAME
   * */
  void closeSourceStreams();

  /** @brief used to load and populate the ResourceLoaderCfg
   *
   *  @returns int32_t - error code
   * */
  int32_t readEngineBinHeaders(ResourceLoaderCfg* outCfg);

  /** @brief used to read  total count of widgets
   *         and their respective file size from  _RESOURCES_BIN_NAME
   *
   *  @param uint64_t * - total static widgets count
   *  @param uint64_t * - total dynamic widgets count
   *  @param int32_t *  - total widgets file size
   *
   *  @returns int32_t  - error code
   * */
  int32_t readResourceBinHeader(uint64_t* outStaticWidgetsSize,
                                uint64_t* outDynamicWidgetsSize,
                                int32_t* outWidgetFileSize);

  /** @brief used to read  total count of fonts
   *         and their respective file size from  _FONTS_BIN_NAME
   *
   *  @param uint64_t * - total fonts count
   *  @param int32_t *  - total fonts file size
   *
   *  @returns int32_t  - error code
   * */
  int32_t readFontBinHeader(uint64_t* outFontsSize, int32_t* outFontsFileSize);

  /** @brief used to read  total count of musics and sound chunks
   *         and their respective file size from  _SOUNDS_BIN_NAME
   *
   *  @param uint64_t * - total musics count
   *  @param uint64_t * - total sound chunks count
   *  @param int32_t *  - total sounds file size
   *
   *  @returns int32_t  - error code
   * */
  int32_t readSoundBinHeader(uint64_t* outMusicsSize, uint64_t* outChunksSize,
                             int32_t* outSoundsFileSize);

  /** @brief used to parse single DataHeader from
   *         _RESOURCES_BIN_NAME, _FONTS_BIN_NAME and _SOUNDS_BIN_NAME
   *                                          (they share common header).
   *
   *  @param const FieldType - IMAGE, SPRITE or FONT
   *  @param DataHeader *    - fully parsed DataHeader chunk
   *
   *  @return bool           - successful read or not
   *
   *                 NOTE: unsuccessful read means
   *                                destinationStream.eof() is reached.
   * */
  bool readChunkHeaderInternal(const ResourceDefines::FieldType fieldType,
                               DataHeader* outData);

  // Hold the name of the project resource file
  const std::string _RESOURCES_BIN_NAME;

  // Hold the name of the project font file
  const std::string _FONTS_BIN_NAME;

  // Hold the name of the project font file
  const std::string _SOUNDS_BIN_NAME;

  // Holds the name of the current project folder
  const std::string _PROJECT_NAME;

  // Holds the name of the root project folder
  std::string _projectFolder;

  // Input file stream for the project resource file
  std::ifstream _resSourceStream;

  // Input file stream for the project font file
  std::ifstream _fontsSourceStream;

  // Input file stream for the project sounds file
  std::ifstream _soundsSourceStream;
};

#endif /* UTILS_INCLUDE_RESOURCELOADER_RESOURCELOADER_H_ */
