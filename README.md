# utils

## A helper static C++ library with random utilities
The library is optimized for fast compilation.

Example use cases
- Time measurements
- Colored logging
- Symbol visibility
- Basic 2D drawing shapes
- etc ...

## Usage from plain CMake
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

## Usage as part of ROS1(catkin) / ROS2(colcon) meta-build systems
- consume directly with find_package(utils) in the package CMakeLists.txt
- Link agains your target
- The library automatically exposes ans install it's artifacts following ROS1/ROS2 structure
- Example usage project: https://github.com/zhivkopetrov/robotics_v1

## Dependencies
- cmake_helpers - https://github.com/zhivkopetrov/cmake_helpers.git

## Supported Platforms
Linux:
  - g++ 12
  - clang++ 14
  - Emscripten (em++) 3.1.28
  - Robot Operating System 2 (ROS2)
    - Through colcon meta-build system (CMake based)
  - Robot Operating System 1 (ROS1)
    - Through catkin meta-build system (CMake based)
      - Due to soon ROS1 end-of-life catkin builds are not actively supported

Windows:
  - MSVC++ (>= 14.20) Visual Studio 2019