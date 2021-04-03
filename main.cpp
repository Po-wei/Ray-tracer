#include <iostream>
#include <vector>
#include <array>

#include "vec3.h"
#include "common.h"
#include "color.h"



int main() {

    // Render

    canvas cvs;
    for (int j = IMAGE_HEIGHT-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {

            auto r = double(i) / (IMAGE_WIDTH-1);
            auto g = double(j) / (IMAGE_HEIGHT-1);
            auto b = 0.25;
            std::cout <<color(r,g,b) <<std::endl;
            cvs[IMAGE_HEIGHT-1-j][i] = color(r,g,b);
        }
    }
    std::cerr << "\rDone" << std::flush;
    writeImage("main.png", cvs);
}