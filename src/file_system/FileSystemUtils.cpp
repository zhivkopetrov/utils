// Corresponding header
#include "utils/file_system/FileSystemUtils.h"

// System headers
#include <filesystem>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"
#include "utils/Log.h"

namespace {
namespace fs = std::filesystem;
constexpr auto buildDirName = "build";
}

std::string FileSystemUtils::getCurrentWorkingDirectory() {
  std::error_code errCode;
  const fs::path currPath = fs::current_path(errCode);
  if (errCode) {
    LOGERR("filesystem::current_path() failed. Reason: %s", errCode.message().c_str());
    return "";
  }

  return currPath.string();
}

std::string FileSystemUtils::getRootDirectory() {
  const std::string currDir = getCurrentWorkingDirectory();
  if (currDir.empty()) {
    LOGERR("getCurrentWorkingDirectory(), returning empty result");
    return std::string { };
  }

  const size_t buildDirPos = currDir.rfind(buildDirName);
  //build not found -> this means cwd is in top level (above build)
  if (std::string::npos == buildDirPos) {
    return currDir + "/";
  }

  return currDir.substr(0, buildDirPos);
}

std::string FileSystemUtils::getBuildDirectory() {
  const std::string buildDir = FileSystemUtils::getRootDirectory()
      + buildDirName + "/";
  if (buildDir == buildDirName) {
    LOGERR(
        "Error, FileSystemUtils::getRootDirectory(), returning empty result");
    return std::string { };
  }

  return buildDir;
}

std::string FileSystemUtils::getFileNameFromAbsolutePath(
    const std::string &fileAbsPath) {
  const size_t slashPos = fileAbsPath.rfind("/");
  if (std::string::npos == slashPos) {
    return fileAbsPath; //is root dir
  }

  return fileAbsPath.substr(slashPos + 1, fileAbsPath.size() - slashPos - 1);
}

bool FileSystemUtils::isDirectoryPresent(const std::string &dicrectoryAbsPath) {
  return fs::exists(dicrectoryAbsPath);
}

ErrorCode FileSystemUtils::createDirectory(
    const std::string &dicrectoryAbsPath) {
  std::error_code errCode;
  fs::create_directory(dicrectoryAbsPath, errCode);
  if (errCode) {
      LOGERR("Error, filesystem::create_directory() failed for directory '%s', Reason: %s",
             dicrectoryAbsPath.c_str(), errCode.message().c_str());
      return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode FileSystemUtils::createDirectoryRecursive(
    const std::string &dicrectoryAbsPath) {
  std::error_code errCode;
  fs::create_directories(dicrectoryAbsPath, errCode);
  if (errCode) {
      LOGERR("Error, filesystem::create_directories() failed for directory '%s', Reason: %s",
             dicrectoryAbsPath.c_str(), errCode.message().c_str());
      return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode FileSystemUtils::getAllFilesInDirectoryRecursively(
    const std::string &dir,
    const std::vector<std::string> &blackListFolderNames,
    std::vector<std::string> &outFilesAbsPath) {
  std::error_code errCode;
  std::string currEntryStr;

  for (const fs::directory_entry& dirEntry : 
        fs::recursive_directory_iterator(dir)) {
    currEntryStr = dirEntry.path().string();

    const bool isDirectory = dirEntry.is_directory(errCode);
    if (errCode) {
      LOGERR("Error, filesystem::is_directory() failed for directory '%s', Reason: %s",
        currEntryStr.c_str(), errCode.message().c_str());
      return ErrorCode::FAILURE;
    }
    
    if (isDirectory) {
      for (const auto &blackListDirName : blackListFolderNames) {
        const bool found = std::string::npos != blackListDirName.rfind(currEntryStr);
        if (found) {
          //skip the black listed directory
          continue;
        }
      }
    }

    const bool isRegularFile = dirEntry.is_regular_file(errCode);
    if (errCode) {
      LOGERR("Error, filesystem::is_regular_file() failed for directory '%s', Reason: %s",
        currEntryStr.c_str(), errCode.message().c_str());
      return ErrorCode::FAILURE;
    }

    const bool isSymlink = dirEntry.is_symlink(errCode);
    if (errCode) {
      LOGERR("Error, filesystem::is_symlink() failed for directory '%s', Reason: %s",
        currEntryStr.c_str(), errCode.message().c_str());
      return ErrorCode::FAILURE;
    }

    //skip if not regular file
    if (!isRegularFile || isSymlink) {
      continue;
    }

    outFilesAbsPath.emplace_back(currEntryStr);
  }

  return ErrorCode::SUCCESS;
}
