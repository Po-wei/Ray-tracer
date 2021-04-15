#include <iostream>

#include "common.h"
#include "image.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;
    if(depth <= 0)
    {
        return color(0, 0, 0);
    }
    if(world.hit(r, 0, infinity, rec))
    {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        vec3 reflect = target - rec.p;
        return 0.5 * ray_color(ray(rec.p, reflect), world, depth-1);
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
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    // Camera
    camera cam;

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    
    // Render

    canvas cvs(image_height, std::vector<color>(image_width, color{0,0,0}));

    for (int i = 0; i < image_height; i++)
    {
        for (int j = 0; j < image_width; j++)
        {
            for(int s = 0; s < samples_per_pixel; s++)
            {
                auto v = double(image_height - 1 - i + random_double(-0.5, 0.5)) / (image_height - 1);
                auto u = double(j + random_double(-0.5, 0.5)) / (image_width - 1);
                ray r = cam.get_ray(u,v);
                cvs[i][j] += ray_color(r, world, max_depth);
            }
        }
    }
    std::cerr << "\rDone" << std::flush;
    writeImage("main.png", cvs, samples_per_pixel);
}
