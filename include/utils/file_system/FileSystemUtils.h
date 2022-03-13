#ifndef UTILS_FILESYSTEMUTILS_H_
#define UTILS_FILESYSTEMUTILS_H_

// System headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward Declarations

class FileSystemUtils {
public:
  FileSystemUtils() = delete;

  static std::string getCurrentWorkingDirectory();

  static std::string getRootDirectory();

  static std::string getBuildDirectory();

  static std::string getFileNameFromAbsolutePath(
      const std::string &fileAbsPath);

  static bool isDirectoryPresent(const std::string &dicrectoryAbsPath);

  static ErrorCode createDirectory(const std::string &dicrectoryAbsPath);

  static ErrorCode createDirectoryRecursive(
      const std::string &dicrectoryAbsPath);

  static ErrorCode getAllFilesInDirectoryRecursively(
      const std::string &dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath);

private:
  static void parseDirectory(
      const std::string &dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath, ErrorCode &errCode);
};

#endif /* UTILS_FILESYSTEMUTILS_H_ */
