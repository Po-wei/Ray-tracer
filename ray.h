#ifndef RAY_H
#define PAY_H

#include "vec3.h"

class ray
{
public:
    ray() {}
    ray(const point3 &p, const vec3 &d)
        : orig(p), dir(d)
    {
    }

    point3 origin() const
    {
        return orig;
    }

    vec3 direction() const
    {
        return dir;
    }

    point3 at(double t) const
    {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif