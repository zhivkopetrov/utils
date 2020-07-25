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
#include "utils/ErrorCode.h"
#include "utils/Log.h"

namespace {
constexpr auto buildDirName = "build";
}

std::string FileSystemUtils::getCurrentWorkingDirectory() {
  char cwd[PATH_MAX];
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

  const size_t buildDirPos = currDir.rfind(buildDirName);
  if (std::string::npos == buildDirPos) {
    LOGERR(
      "Error, '%s' directory not found in currentWorkingDirectory: %s, "
      "returning empty result", buildDirName, currDir.c_str());
    return std::string{};
  }

  return currDir.substr(0, buildDirPos);
}

std::string FileSystemUtils::getBuildDirectory() {
  const std::string buildDir =
      FileSystemUtils::getRootDirectory() + buildDirName + "/";
  if (buildDir == buildDirName) {
    LOGERR(
      "Error, FileSystemUtils::getRootDirectory(), returning empty result");
    return std::string{};
  }

  return buildDir;
}

std::string FileSystemUtils::getFileNameFromAbsolutePath(
      const std::string &fileAbsPath) {
  const size_t slashPos = fileAbsPath.rfind("/");
  if (std::string::npos == slashPos) {
    return fileAbsPath; //is root dir
  }

  return fileAbsPath.substr(
      slashPos + 1, fileAbsPath.size() - slashPos - 1);
}

bool FileSystemUtils::isDirectoryPresent(const std::string &dicrectoryAbsPath) {
  struct stat fileStat;

  // check if directory valid
  if (-1 == stat(dicrectoryAbsPath.c_str(), &fileStat)) {
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
    if (errno != EEXIST) {
      LOGERR("Error, ::mkdir() failed for directory '%s', Reason: %s",
          dicrectoryAbsPath.c_str(), strerror(errno));
      return FAILURE;
    }
  }

  return SUCCESS;
}

int32_t FileSystemUtils::createDirectoryRecursive(
    const std::string &dicrectoryAbsPath) {
  if (dicrectoryAbsPath.size() > PATH_MAX - 1) {
      errno = ENAMETOOLONG;
      return FAILURE;
  }

  std::string path = dicrectoryAbsPath;
  char *p = nullptr;

  /* Iterate the string */
  for (p = &path[1]; *p; ++p) {
      if (*p == '/') {
          /* Temporarily truncate */
          *p = '\0';

          if (SUCCESS != FileSystemUtils::createDirectory(path)) {
            return FAILURE;
          }

          *p = '/';
      }
  }

  if (SUCCESS != FileSystemUtils::createDirectory(path)) {
    return FAILURE;
  }

  return 0;
}

int32_t FileSystemUtils::getAllFilesInDirectoryRecursively(
      const std::string& dir,
      const std::vector<std::string> &blackListFolderNames,
      std::vector<std::string> &outFilesAbsPath) {
  int32_t err = SUCCESS;
  parseDirectory(dir, blackListFolderNames, outFilesAbsPath, err);
  return err;
}

void FileSystemUtils::parseDirectory(
    const std::string &dir,
    const std::vector<std::string> &blackListFolderNames,
    std::vector<std::string> &outFilesAbsPath, int32_t &errCode) {

  if (SUCCESS != errCode) {
    return;
  }

  DIR* currentDir = nullptr;

  currentDir = opendir(dir.c_str());
  if (nullptr == currentDir) {
    LOGERR("Error in opendir(%s), reason: %s", dir.c_str(), strerror(errno));
    errCode = FAILURE;
  }

  if (SUCCESS == errCode) {
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

  if (SUCCESS != closedir(currentDir)) {
    LOGERR("Error in closedir(), reason: %s", strerror(errno));
    errCode = FAILURE;
  }
}


