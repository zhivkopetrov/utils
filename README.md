# utils

**A helper static C++ library with random trivial implementation optimized for fast compilation**

Example use cases
- Time measurements
- Colored logging
- Symbol visibility
- Basic 2D drawing shapes
- etc ...


**Usage from plain CMake**
- consume directly with find_package(utils) in a CMakeLists.txt
- Link against your target with suitable access modifier
```
target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
        utils::utils
)
```
- Example usage project: https://github.com/zhivkopetrov/dev_battle.git


**Usage as part of ROS(catkin) / ROS2(colcon) meta-build systems**
- consume directly with find_package(utils) in the package CMakeLists.txt
- Link agains your target
- The library automatically exposes ans install it's artifacts following ROS/ROS2 structure
- Example usage project: https://github.com/zhivkopetrov/robotics_v1


**Dependencies**
- cmake_helpers - https://github.com/zhivkopetrov/cmake_helpers.git
- The provided library CMakeLists.txt assumes the helpers.cmake from cmake_helpers repo have already been included


**Platform support**
- Tested on Unix
- Implementation is mostly cross-platform, but still contains several Unix specific implementation(to be fix at some point)