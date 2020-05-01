#author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

if(TARGET utils)
  return()
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

project(utils)
            
set(_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/utils")

add_library(
    ${PROJECT_NAME} 
    STATIC
        "${_SRC_DIR}/common/CircularBuffer.cpp"
        "${_SRC_DIR}/common/Crc.cpp"
        "${_SRC_DIR}/common/Position.cpp"
        "${_SRC_DIR}/datatype/FloatingPointUtils.cpp"
        "${_SRC_DIR}/datatype/IntegerUtils.cpp"
        "${_SRC_DIR}/datatype/StringUtils.cpp"
        "${_SRC_DIR}/debug/SignalHandler.cpp"
        "${_SRC_DIR}/drawing/Color.cpp"
        "${_SRC_DIR}/drawing/Margins.cpp"
        "${_SRC_DIR}/drawing/Point.cpp"
        "${_SRC_DIR}/drawing/Rectangle.cpp"
        "${_SRC_DIR}/drawing/Sprite.cpp"
        "${_SRC_DIR}/drawing/WidgetAligner.cpp"
        "${_SRC_DIR}/rng/RNG.cpp"
        "${_SRC_DIR}/time/Time.cpp"
)

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        VERSION 1.0.0
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)

if(BUILD_LIKE_POSITION_INDEPENDANT_CODE)
    enable_target_position_independent_code(${PROJECT_NAME})
endif()              



