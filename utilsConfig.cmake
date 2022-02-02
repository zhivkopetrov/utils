include(CMakeFindDependencyMacro)

if(NOT TARGET utils::utils)
  include(${CMAKE_CURRENT_LIST_DIR}/utilsTargets.cmake)
endif()

# This is for catkin compatibility.
set(utils_LIBRARIES utils::utils)

get_target_property(
    utils_INCLUDE_DIRS
    utils::utils
    INTERFACE_INCLUDE_DIRECTORIES
)

