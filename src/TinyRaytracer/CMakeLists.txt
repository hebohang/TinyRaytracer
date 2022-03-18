add_executable(TinyRaytracer)

target_sources(TinyRaytracer
PRIVATE
    "TinyRaytracer.cpp"
    "TinyRaytracer.h"
)

target_link_libraries(TinyRaytracer PRIVATE
    stb_image
    camera
    glfw
    ${OPENGL_LIBRARIES}
)

target_include_directories(TinyRaytracer PRIVATE
    ${PROJECT_SOURCE_DIR}/src/vendor
)