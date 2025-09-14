#pragma once

#include "Interval.hpp"
#include "Vector.hpp"
#include <iostream>

using Color = Vector3;

inline double LinearToGamma(double linearComponent)
{
    return linearComponent > 0 ? std::sqrt(linearComponent) : 0;
}

inline void WriteColor(std::ostream& out, const Color& color)
{
    static const Interval intensity(0, 1);
    int r = intensity.clamp(LinearToGamma(color.x())) * 255;
    int g = intensity.clamp(LinearToGamma(color.y())) * 255;
    int b = intensity.clamp(LinearToGamma(color.z())) * 255;
    out << r << ' ' << g << ' ' << b << '\n';
}
