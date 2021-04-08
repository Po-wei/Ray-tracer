#include <iostream>
#include <vector>
#include <array>

#include "vec3.h"
#include "common.h"
#include "image.h"
#include "ray.h"


color ray_color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{

    // Camera
    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATIO * viewport_height;
    double focal_length = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render

    canvas cvs;
    for (int i = 0; i < IMAGE_HEIGHT; i++)
    {
        for (int j = 0; j < IMAGE_WIDTH; j++)
        {
            auto v = double(IMAGE_HEIGHT-1-i) / (IMAGE_HEIGHT - 1);
            auto u = double(j) / (IMAGE_WIDTH - 1);
            ray r(origin, lower_left + u * horizontal + v * vertical - origin);
            cvs[i][j] = ray_color(r);
        }
    }
    std::cerr << "\rDone" << std::flush;
    writeImage("main.png", cvs);
}
