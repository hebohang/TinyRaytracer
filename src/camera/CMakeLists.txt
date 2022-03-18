add_library(camera STATIC)

target_sources(camera PRIVATE
    Camera.h
    Camera.cpp
)

target_include_directories(camera PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}/src/vendor
)