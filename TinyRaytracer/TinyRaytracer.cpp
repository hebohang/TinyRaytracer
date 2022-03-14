#include "stb_image.h"
#include <iostream>
#include <string>

int main()
{
    const std::string ProjPath(PROJECT_PATH);
    std::string PhotoPath = ProjPath + std::string("/resource/laotouhuan.jpg");
    int weight, height, n;
    unsigned char* idata = stbi_load(PhotoPath.c_str(), &weight, &height, &n, 0);
    std::cout << "The photo weight: " << weight << std::endl;
    std::cout << "The photo height: " << height << std::endl;
}