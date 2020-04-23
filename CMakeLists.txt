#author Zhivko Petrov

cmake_minimum_required(VERSION 3.5.1)

include(cmake_modules/helpers.cmake)

project(utils)

set(_UTILS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(_UTILS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
            
#Generate the static library from the sources
add_library(
    ${PROJECT_NAME} 
    STATIC
        ""
)

target_sources(${PROJECT_NAME} PUBLIC
    "${_UTILS_SRC_DIR}/common/CircularBuffer.cpp"
    "${_UTILS_SRC_DIR}/common/Crc.cpp"
    "${_UTILS_SRC_DIR}/common/Position.cpp"
    "${_UTILS_SRC_DIR}/common/ResourceFileHeader.cpp"
    "${_UTILS_SRC_DIR}/datatype/FloatingPointUtils.cpp"
    "${_UTILS_SRC_DIR}/datatype/IntegerUtils.cpp"
    "${_UTILS_SRC_DIR}/datatype/StringUtils.cpp"
    "${_UTILS_SRC_DIR}/debug/SignalHandler.cpp"
    "${_UTILS_SRC_DIR}/drawing/Color.cpp"
    "${_UTILS_SRC_DIR}/drawing/Margins.cpp"
    "${_UTILS_SRC_DIR}/drawing/Point.cpp"
    "${_UTILS_SRC_DIR}/drawing/Rectangle.cpp"
    "${_UTILS_SRC_DIR}/drawing/Sprite.cpp"
    "${_UTILS_SRC_DIR}/drawing/WidgetAligner.cpp"
    "${_UTILS_SRC_DIR}/resourceloader/ResourceLoader.cpp"
    "${_UTILS_SRC_DIR}/rng/RNG.cpp"
    "${_UTILS_SRC_DIR}/sound/CommonSoundDefines.cpp"
    "${_UTILS_SRC_DIR}/time/Time.cpp"
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
        ${CMAKE_SOURCE_DIR}
    PRIVATE
        ${_UTILS_INCLUDE_DIR}
)

#invoke include-what-you-use (if it's enabled) for the current project
if(USE_IWYU)
    enable_target_include_what_you_use(${PROJECT_NAME})
endif(USE_IWYU)

if(BUILD_LIKE_POSITION_INDEPENDANT_CODE)
    enable_target_position_independent_code(${PROJECT_NAME})
endif()              



