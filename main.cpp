#include <iostream>

#include "common.h"
#include "image.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <algorithm>

color ray_color(const ray &r, const hittable &world, int depth)
{
    hit_record rec;
    if(depth <= 0)
    {
        return color(0, 0, 0);
    }
    if(world.hit(r, 0.001, infinity, rec))
    {
        ray scatter;
        color attenation;
        if(rec.mat_ptr->scatter(r, rec, attenation, scatter))
        {
            return attenation * ray_color(scatter, world, depth-1);
        }
        else
        {
            return color(0,0,0);
        }
    }
   
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    // Camera
    camera cam;

    // world
    hittable_list world;
    // world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.6, 0.6, 0.6));
    auto material_right  = make_shared<metal>(color(0.6, 0.6, 0.6));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    
    // Render

    canvas cvs(image_height, std::vector<color>(image_width, color{0,0,0}));

    for (int i = 0; i < image_height; i++)
    {
        std::cerr << "\rScanlines remaining: " << image_height - 1 - i << ' ';
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
