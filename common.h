#ifndef COMMON_H
#define COMMON_H

#include <memory>
#include <limits>
#include <random>

#include "vec3.h"
#include "ray.h"



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




inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    // need seed
    static std::mt19937 generator;
    return distribution(generator);
}



#endif