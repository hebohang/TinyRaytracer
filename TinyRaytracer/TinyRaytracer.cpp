#include "stb_image.h"
#include "stb_image_write.h"
#include "geometry.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

void render()
{
    const std::string ProjPath(PROJECT_PATH);
    const std::string ResoucePath = ProjPath + std::string("/resource");

    if (!std::filesystem::exists(ResoucePath))
        std::filesystem::create_directories(ResoucePath);

    std::string OutPath = ResoucePath + std::string("/out.png");
    const int width = 1024;
    const int height = 768;
    std::vector<Vec3f> framebuffer(width * height);

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0);
        }
    }

    std::stringstream ss;
    for (size_t i = 0; i < height * width; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            ss << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }

    stbi_write_png(OutPath.c_str(), width, height, 3, ss.str().c_str(), 0);
}

int main()
{
    render();
}