#author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

if(TARGET utils)
  return()
endif()

if(NOT CMAKE_HELPERS_INCLUDED)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)
endif()

project(utils)

set(_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/utils")
set(_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/utils")

add_library(
    ${PROJECT_NAME} 
    STATIC
        "${_INCLUDE_DIR}/common/defines/SymbolNameDefines.h"
        "${_INCLUDE_DIR}/common/AutoCircularBuffer.hpp"
        "${_INCLUDE_DIR}/common/CircularBuffer.h"
        "${_INCLUDE_DIR}/common/Crc.h"
        "${_INCLUDE_DIR}/common/Position.h"
        "${_INCLUDE_DIR}/concurrency/ThreadSafeQueue.hpp"
        "${_INCLUDE_DIR}/data_type/EnumClassUtils.hpp"
        "${_INCLUDE_DIR}/data_type/FloatingPoint.h"
        "${_INCLUDE_DIR}/data_type/FloatingPointUtils.h"
        "${_INCLUDE_DIR}/data_type/IntegerUtils.h"
        "${_INCLUDE_DIR}/data_type/StringUtils.h"
        "${_INCLUDE_DIR}/debug/FunctionTracer.hpp"
        "${_INCLUDE_DIR}/debug/SignalHandler.h"
        "${_INCLUDE_DIR}/debug/StackTrace.hpp"
        "${_INCLUDE_DIR}/file_system/FileSystemUtils.h"
        "${_INCLUDE_DIR}/rng/RNG.h"
        "${_INCLUDE_DIR}/time/Time.h"
        "${_INCLUDE_DIR}/time/TimerDefines.h"
        "${_INCLUDE_DIR}/LimitValues.hpp"
        "${_INCLUDE_DIR}/Log.h"
        
        "${_SRC_DIR}/common/CircularBuffer.cpp"
        "${_SRC_DIR}/common/Crc.cpp"
        "${_SRC_DIR}/common/Position.cpp"
        "${_SRC_DIR}/data_type/FloatingPointUtils.cpp"
        "${_SRC_DIR}/data_type/IntegerUtils.cpp"
        "${_SRC_DIR}/data_type/StringUtils.cpp"
        "${_SRC_DIR}/debug/SignalHandler.cpp"
        "${_SRC_DIR}/drawing/Color.cpp"
        "${_SRC_DIR}/drawing/Margins.cpp"
        "${_SRC_DIR}/drawing/Point.cpp"
        "${_SRC_DIR}/drawing/Rectangle.cpp"
        "${_SRC_DIR}/drawing/WidgetAligner.cpp"
        "${_SRC_DIR}/file_system/FileSystemUtils.cpp"
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



