#include "stb_image.h"
#include "stb_image_write.h"
#include "geometry.h"
#include <omp.h>
#include <iostream>
#include <string>
#include <numbers>
#include <vector>
#include <sstream>
#include <filesystem>

struct Sphere 
{
    Vec3f center;
    float radius;

    Sphere(const Vec3f& c, const float& r) : center(c), radius(r) {}

    bool ray_intersect(const Vec3f& orig, const Vec3f& dir, float& t0) const 
    {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

Vec3f cast_ray(const Vec3f& orig, const Vec3f& dir, const Sphere& sphere) 
{
    float sphere_dist = std::numeric_limits<float>::max();
    if (!sphere.ray_intersect(orig, dir, sphere_dist)) 
    {
        return Vec3f(0.2f, 0.7f, 0.8f); // background color
    }
    return Vec3f(0.4f, 0.4f, 0.3f);
}

void render(const Sphere& sphere)
{
    const std::string ProjPath(PROJECT_PATH);
    const std::string ResoucePath = ProjPath + std::string("/resource");

    if (!std::filesystem::exists(ResoucePath))
        std::filesystem::create_directories(ResoucePath);

    std::string OutPath = ResoucePath + std::string("/out.png");
    const int width = 1024;
    const int height = 768;
    const double fov = std::numbers::pi / 2.;
    std::vector<Vec3f> framebuffer(width * height);

#pragma omp parallel for
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5f) / (float)width - 1.0f) * (float)tan(fov / 2.) * (float)width / (float)height;
            float y = -(2 * (j + 0.5f) / (float)height - 1.0f) * (float)tan(fov / 2.);
            Vec3f dir = Vec3f(x, y, -1.0f).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3f(0.0f, 0.0f, 0.0f), dir, sphere);
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
    Sphere sphere(Vec3f(-3.0f, 0.0f, -16.0f), 2);
    render(sphere);
}
