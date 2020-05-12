#ifndef UTILS_FILESYSTEMUTILS_H_
#define UTILS_FILESYSTEMUTILS_H_

// C system headers

// C++ system headers
#include <string>

// Other libraries headers

// Own components headers

// Forward Declarations

class FileSystemUtils {
public:
  FileSystemUtils() = delete;

  static std::string getCurrentWorkingDirectory();
};

#endif /* UTILS_FILESYSTEMUTILS_H_ */
