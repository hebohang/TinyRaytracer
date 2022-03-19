cmake_minimum_required (VERSION 3.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

project(TinyRaytracer LANGUAGES C CXX)

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "TinyRaytracer only supports 64-bit platforms")
endif ()

if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "The binary directory of CMake cannot be the same as source directory!")
endif()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if (NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(src)