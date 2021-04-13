#include <iostream>
#include <vector>
#include <array>

#include "vec3.h"
#include "common.h"
#include "image.h"
#include "ray.h"


double hit_sphere(const point3& C, double radius, const ray& r)
{
    point3 A = r.origin();
    double c = dot(A-C, A-C) - radius*radius;
    double b = 2 * dot(r.direction(), A-C);
    double a = dot(r.direction(), r.direction());
    double det = b*b - 4*a*c;
    if( det < 0 )
    {
        return -1;
    }
    else
    {
        return (-b - sqrt(det))/ (2 * a);
    }

}

color ray_color(const ray& r)
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);

    if(t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() +1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
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

    canvas cvs(IMAGE_HEIGHT, std::vector<color>(IMAGE_WIDTH));
    
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
