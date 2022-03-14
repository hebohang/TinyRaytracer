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