#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
using canvas = std::vector<std::vector<color>>;

void writeImage(std::string fileName, canvas &cvs)
{
    if(cvs.size() == 0) return;
    int image_height = cvs.size();
    int image_width = cvs[0].size();
    uint8_t* data = new uint8_t [3 * image_width * image_height];
    int index = 0;
    for(auto line : cvs)
    {
        for(auto c : line)
        {
            data[index++] = static_cast<uint8_t>(255.999 * c.x());
            data[index++] = static_cast<uint8_t>(255.999 * c.y());
            data[index++] = static_cast<uint8_t>(255.999 * c.z());
        }
    }
    stbi_write_png(fileName.c_str(), image_width, image_height, 3, data, 0);
}


#endif