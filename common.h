#ifndef COMMON_H
#define COMMON_H

#include <memory>
#include <limits>
#include <random>


// Usings

using std::sqrt;
using std::shared_ptr;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double(double start, double end) {
    static std::uniform_real_distribution<double> distribution(start, end);
    // need seed
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double v, double min_val, double max_val)
{
    if(v < min_val)
    {
        return min_val;
    }
    else if(v > max_val)
    {
        return max_val;
    }
    else
    {
        return v;
    }
}

#include "vec3.h"
#include "ray.h"

#endif