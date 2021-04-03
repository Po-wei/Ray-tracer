#ifndef COLOR_H
#define COLOR_H
#include <string>
#include "common.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void writeImage(std::string fileName, canvas &cvs)
{
    uint8_t* data = new uint8_t [3 * IMAGE_WIDTH * IMAGE_HEIGHT];
    
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
    stbi_write_png(fileName.c_str(), IMAGE_WIDTH, IMAGE_HEIGHT, 3, data, 0);
}


#endif