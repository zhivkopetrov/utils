// Corresponding header
#include "utils/file_system/FileSystemUtils.h"

// C++ system headers
#include <unistd.h>

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
