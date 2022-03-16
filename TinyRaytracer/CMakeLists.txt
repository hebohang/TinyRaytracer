add_executable(TinyRaytracer)

target_sources(TinyRaytracer
PRIVATE
    "TinyRaytracer.cpp"
    "TinyRaytracer.h"
    "geometry.h"
)

target_link_libraries(TinyRaytracer PRIVATE
    stb_image
)

target_include_directories(TinyRaytracer PRIVATE
    ${PROJECT_SOURCE_DIR}/vendor
)