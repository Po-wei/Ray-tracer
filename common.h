#ifndef COMMON_H
#define COMMON_H

#include <array>
#include "vec3.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

typedef std::array<std::array<color, IMAGE_WIDTH>, IMAGE_HEIGHT> canvas;



#endif