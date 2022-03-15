add_library(stb_image STATIC)

target_sources(stb_image PRIVATE
    stb_image.h
    stb_image_write.h
    stb_image.cpp
)

target_include_directories(stb_image INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR} 
)