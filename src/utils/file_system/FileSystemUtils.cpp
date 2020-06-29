// Corresponding header
#include "utils/file_system/FileSystemUtils.h"

// C system headers
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// C++ system headers
#include <cstring>
#include <cerrno>

// Other libraries headers

// Own components headers
#include "utils/Log.h"

std::string FileSystemUtils::getCurrentWorkingDirectory() {
  char cwd[512];
  if (nullptr != getcwd(cwd, sizeof(cwd))) {
      return std::string(cwd);
  }

  LOGERR("getcwd() failed, Reason: %s", strerror(errno));
  return std::string{};
}

std::string FileSystemUtils::getRootDirectory() {
  const std::string currDir = getCurrentWorkingDirectory();
  if (currDir.empty()) {
    LOGERR("getCurrentWorkingDirectory(), returning empty result");
    return std::string{};
  }

  constexpr auto buildDirName = "build";
  const size_t buildDirPos = currDir.rfind(buildDirName);
  if (std::string::npos == buildDirPos) {
    LOGERR(
      "Error, '%s' directory not found, returning empty result", buildDirName);
    return std::string{};
  }

  return currDir.substr(0, buildDirPos);
}

std::string FileSystemUtils::getCurrentFolderFromDirectory(
      const std::string &dicrectoryAbsPath) {
  const size_t slashPos = dicrectoryAbsPath.rfind("/");
  if (std::string::npos == slashPos) {
    return dicrectoryAbsPath; //is root dir
  }
  return dicrectoryAbsPath.substr(
      slashPos, dicrectoryAbsPath.size() - slashPos - 1);
}

bool FileSystemUtils::isDirectoryPresent(const std::string &dicrectoryAbsPath) {
  struct stat fileStat;

  // check if directory valid
  if (-1 == stat(dicrectoryAbsPath.c_str(), &fileStat)) {
    LOGERR("Error, ::stat() failed for directory '%s', Reason: %s",
        dicrectoryAbsPath.c_str(), strerror(errno));
    return false;
  }

  if (!S_ISDIR(fileStat.st_mode)) {
    return false;
  }

  return true;
}

int32_t FileSystemUtils::createDirectory(const std::string &dicrectoryAbsPath) {
  // create folder with read/write/search permissions for owner and
  // group, with read/search permissions for others
  if (-1 == mkdir(dicrectoryAbsPath.c_str(),
                  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
    LOGERR("Error, ::mkdir() failed for directory '%s', Reason: %s",
        dicrectoryAbsPath.c_str(), strerror(errno));
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int32_t FileSystemUtils::getAllFilesInDirectoryRecursively(
      const std::string& dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath) {
  int32_t err = EXIT_SUCCESS;
  parseDirectory(dir, blackListFolderNames, outFilesAbsPath, err);
  return err;
}

void FileSystemUtils::parseDirectory(
    const std::string &dir,
    const std::vector<std::string> &blackListFolderNames,
    std::vector<std::string> &outFilesAbsPath, int32_t &errCode) {

  if (EXIT_SUCCESS != errCode) {
    return;
  }

  DIR* currentDir = nullptr;

  currentDir = opendir(dir.c_str());
  if (nullptr == currentDir) {
    LOGERR("Error in opendir(%s), reason: %s", dir.c_str(), strerror(errno));
    errCode = EXIT_FAILURE;
  }

  if (EXIT_SUCCESS == errCode) {
    struct dirent* dirP = nullptr;
    std::string filePath = "";

    while (nullptr != (dirP = readdir(currentDir))) {
      // Skip current object if it is this directory or parent directory
      if (!strncmp(dirP->d_name, ".", 1) || !strncmp(dirP->d_name, "..", 2)) {
        continue;
      }

      // Constructing absolute file path
      filePath = dir;
      if (dir[dir.size() - 1] != '/') {
        filePath.append("/");
      }
      filePath.append(dirP->d_name);

      if (isDirectoryPresent(filePath)) {
        bool shouldSkipDirectory = false;

        for (const auto &dirName : blackListFolderNames) {
          if (std::string::npos != filePath.rfind(dirName)) {
            //skip the black listed directory
            shouldSkipDirectory = true;
          }
        }
        if (!shouldSkipDirectory) {
          parseDirectory(
              filePath, blackListFolderNames, outFilesAbsPath, errCode);
        }

        continue;
      }

      // Here we are located on the leaf folder nodes (leaf files)
      outFilesAbsPath.emplace_back(filePath);
    }
  }

  if (EXIT_SUCCESS != closedir(currentDir)) {
    LOGERR("Error in closedir(), reason: %s", strerror(errno));
    errCode = EXIT_FAILURE;
  }
}


