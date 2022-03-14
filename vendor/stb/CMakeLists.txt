add_library(stb_image STATIC)

target_sources(stb_image PRIVATE
    stb_image.cpp
    stb_image.h
)

target_include_directories(stb_image INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR} 
)