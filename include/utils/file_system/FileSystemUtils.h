#ifndef UTILS_FILESYSTEMUTILS_H_
#define UTILS_FILESYSTEMUTILS_H_

// C system headers

// C++ system headers
#include <cstdint>
#include <string>
#include <vector>

// Other libraries headers

// Own components headers

// Forward Declarations

class FileSystemUtils {
public:
  FileSystemUtils() = delete;

  static std::string getCurrentWorkingDirectory();

  static std::string getRootDirectory();

  static std::string getCurrentFolderFromDirectory(
      const std::string &dicrectoryAbsPath);

  static bool isDirectoryPresent(const std::string &dicrectoryAbsPath);

  static int32_t createDirectory(const std::string &dicrectoryAbsPath);

  static int32_t getAllFilesInDirectoryRecursively(
      const std::string &dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath);

private:
  static void parseDirectory(
      const std::string &dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath, int32_t &errCode);
};

#endif /* UTILS_FILESYSTEMUTILS_H_ */
