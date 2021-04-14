#include <iostream>

#include "common.h"
#include "image.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray &r, const hittable &world)
{
    hit_record rec;
    if(world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1,1,1));
    }
   
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    // Camera
    camera cam;

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    

    // Render

    canvas cvs(image_height, std::vector<color>(image_width));

    for (int i = 0; i < image_height; i++)
    {
        for (int j = 0; j < image_width; j++)
        {
            auto v = double(image_height - 1 - i) / (image_height - 1);
            auto u = double(j) / (image_width - 1);
            ray r = cam.get_ray(u,v);
            cvs[i][j] = ray_color(r, world);
        }
    }
    std::cerr << "\rDone" << std::flush;
    writeImage("main.png", cvs);
}
