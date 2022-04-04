#author Zhivko Petrov

cmake_minimum_required(VERSION 3.10.2)

project(
    utils 
    LANGUAGES CXX
    VERSION 1.0.0
)

find_package(cmake_helpers REQUIRED)
find_package(Threads REQUIRED)

set(_INC_FOLDER_NAME include)
set(_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}/${PROJECT_NAME})
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME}
    STATIC
        ${_INC_DIR}/common/defines/SymbolNameDefines.h
        ${_INC_DIR}/common/AutoCircularBuffer.h
        ${_INC_DIR}/common/CircularBuffer.h
        ${_INC_DIR}/common/Crc.h
        ${_INC_DIR}/class/NonCopyable.h
        ${_INC_DIR}/class/NonMoveable.h
        ${_INC_DIR}/concurrency/ThreadSafeQueue.h
        ${_INC_DIR}/data_type/EnumClassUtils.h
        ${_INC_DIR}/data_type/FloatingPoint.h
        ${_INC_DIR}/data_type/FloatingPointUtils.h
        ${_INC_DIR}/data_type/IntegerUtils.h
        ${_INC_DIR}/data_type/StringUtils.h
        ${_INC_DIR}/debug/FunctionTracer.h
        ${_INC_DIR}/debug/SignalHandler.h
        ${_INC_DIR}/debug/StackTrace.h
        ${_INC_DIR}/file/IniFileParser.h
        ${_INC_DIR}/file_system/FileSystemUtils.h
        ${_INC_DIR}/time/Time.h
        ${_INC_DIR}/ErrorCode.h
        ${_INC_DIR}/LimitValues.h
        ${_INC_DIR}/Log.h
        ${_INC_DIR}/drawing/Point.h
        ${_INC_DIR}/drawing/Rectangle.h
        ${_INC_DIR}/drawing/Color.h
        ${_INC_DIR}/drawing/Margin.h
        ${_INC_DIR}/drawing/WidgetAligner.h
        ${_INC_DIR}/rng/Rng.h
        
        ${_SRC_DIR}/common/CircularBuffer.cpp
        ${_SRC_DIR}/common/Crc.cpp
        ${_SRC_DIR}/data_type/FloatingPointUtils.cpp
        ${_SRC_DIR}/data_type/IntegerUtils.cpp
        ${_SRC_DIR}/data_type/StringUtils.cpp
        ${_SRC_DIR}/debug/SignalHandler.cpp
        ${_SRC_DIR}/debug/StackTrace.cpp
        ${_SRC_DIR}/drawing/Color.cpp
        ${_SRC_DIR}/drawing/Margin.cpp
        ${_SRC_DIR}/drawing/Point.cpp
        ${_SRC_DIR}/drawing/Rectangle.cpp
        ${_SRC_DIR}/drawing/WidgetAligner.cpp
        ${_SRC_DIR}/file/IniFileParser.cpp
        ${_SRC_DIR}/file_system/FileSystemUtils.cpp
        ${_SRC_DIR}/time/Time.cpp
        ${_SRC_DIR}/rng/Rng.cpp
        ${_SRC_DIR}/log/Log.cpp
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_INC_FOLDER_NAME}>
        $<INSTALL_INTERFACE:${_INC_FOLDER_NAME}>
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        Threads::Threads
)

if(NOT DISABLE_ROS_TOOLING)
    # Ament uses non-monolith build (separate build and install steps).
    # The helpers.cmake has to be included manually.
    # This allows access to the helpers.cmake user defined macros
    # In the case of monolith build - the file is automatically included
    # from the cmake_helpersConfig.cmake when the package is consumed by find_package()
	include(${cmake_helpers_DIR}/helpers.cmake)
	
    enable_ros_tooling_for_target(
        ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/package.xml
    )
endif()

set_target_cpp_standard(${PROJECT_NAME} 20)
enable_target_warnings(${PROJECT_NAME})
set_target_visibility(${PROJECT_NAME})
install_and_export_target(${PROJECT_NAME} ${_INC_FOLDER_NAME})

#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)

if(BUILD_LIKE_POSITION_INDEPENDANT_CODE)
    enable_target_position_independent_code(${PROJECT_NAME})
endif()

