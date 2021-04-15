#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
using canvas = std::vector<std::vector<color>>;

void writeImage(std::string fileName, canvas &cvs, int samples_per_pixel)
{
    if (cvs.size() == 0)
        return;
    int image_height = cvs.size();
    int image_width = cvs[0].size();

    uint8_t *data = new uint8_t[3 * image_width * image_height];
    int index = 0;
    for (auto line : cvs)
    {
        for (auto c : line)
        {
            auto r = sqrt(c.x() / samples_per_pixel);
            auto g = sqrt(c.y() / samples_per_pixel);
            auto b = sqrt(c.z() / samples_per_pixel);
            data[index++] = static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
            data[index++] = static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999));
            data[index++] = static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999));
        }
    }
    stbi_write_png(fileName.c_str(), image_width, image_height, 3, data, 0);
}

#endif