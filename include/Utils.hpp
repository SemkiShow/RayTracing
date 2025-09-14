#pragma once

#include <cstdlib>
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees) { return degrees * pi / 180.0; }
inline double RandomDouble() { return std::rand() / (RAND_MAX + 1.0); }
inline double RandomDouble(double min, double max) { return min + (max - min) * RandomDouble(); }
