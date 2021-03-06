#include "Camera.h"
#include "TinyRaytracer.h"

#include <omp.h>
#include <iostream>
#include <string>
#include <numbers>
#include <vector>
#include <sstream>
#include <filesystem>

#include <stb_image.h>
#include <stb_image_write.h>
#include <Eigen/Dense>
#include <GLFW/glfw3.h>

using Eigen::Vector3f;

struct Sphere 
{
    Vector3f center;
    float radius;

    Sphere(const Vector3f& c, const float& r) : center(c), radius(r) {}

    bool ray_intersect(const Vector3f& orig, const Vector3f& dir, float& t0) const 
    {
        Vector3f L = center - orig;
        float tca = L.dot(dir);
        float d2 = L.dot(L) - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

Vector3f cast_ray(const Vector3f& orig, const Vector3f& dir, const Sphere& sphere) 
{
    float sphere_dist = std::numeric_limits<float>::max();
    if (!sphere.ray_intersect(orig, dir, sphere_dist)) 
    {
        return Vector3f(0.2f, 0.7f, 0.8f); // background color
    }
    return Vector3f(0.4f, 0.4f, 0.3f);
}

void RenderToBuffer(const Camera& cam, const Sphere& sphere, std::stringstream& outBuffer)
{
    const std::string ProjPath(PROJECT_PATH);
    const std::string ResoucePath = ProjPath + std::string("/resource");

    if (!std::filesystem::exists(ResoucePath))
        std::filesystem::create_directories(ResoucePath);

    std::string OutPath = ResoucePath + std::string("/out.png");
    float tanFov2 = (float)tan(cam.GetFov() / 2.);
    std::vector<Vector3f> framebuffer(width * height);

#pragma omp parallel for
    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5f) / (float)width - 1.0f) * tanFov2 * (float)width / (float)height;
            float y = -(2 * (j + 0.5f) / (float)height - 1.0f) * tanFov2;
            // Vector3f dir = Eigen::AngleAxisf(std::numbers::pi / 4, Vector3f(0.0f, 0.0f, 1.0f)).matrix().transpose() * Vector3f(x, y, -1.0f).normalized();
            Vector3f dir = Vector3f(x, y, -1.0f).normalized();
            framebuffer[i + j * width] = cast_ray(cam.GetPos(), dir, sphere);
        }
    }

    for (size_t i = 0; i < height * width; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            outBuffer << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }

    //glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, ss.str().c_str());

    //stbi_write_png(OutPath.c_str(), width, height, 3, ss.str().c_str(), 0);
}

void display(std::stringstream& buffer)
{
    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.str().c_str());
}

int main()
{
    GLFWwindow* window;
    Camera cam;
    Sphere sphere(Vector3f(-3.0f, 0.0f, -16.0f), 2);
    std::stringstream buffer;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        RenderToBuffer(cam, sphere, buffer);
        display(buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
