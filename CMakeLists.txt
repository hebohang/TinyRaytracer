cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("TinyRaytracer")

add_compile_definitions(
    PROJECT_PATH="${PROJECT_SOURCE_DIR}"
)

add_subdirectory(vendor)
add_subdirectory(TinyRaytracer)

