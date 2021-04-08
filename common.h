#ifndef COMMON_H
#define COMMON_H

#include <array>
#include "vec3.h"

const double ASPECT_RATIO = 16.0/9.0;
const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

typedef std::array<std::array<color, IMAGE_WIDTH>, IMAGE_HEIGHT> canvas;



#endif