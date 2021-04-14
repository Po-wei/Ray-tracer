#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class camera
{
public:
    camera();
    ray get_ray(double, double);

private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;

};

camera::camera()
{
    double aspect_ratio = 16.0 / 9.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    this->origin = point3(0, 0, 0);
    this->horizontal = vec3(viewport_width, 0, 0);
    this->vertical = vec3(0, viewport_height, 0);
    this->lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
}

ray camera::get_ray(double u, double v)
{
    return ray(origin, lower_left + u * horizontal + v * vertical - origin);
}

#endif