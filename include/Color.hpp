#pragma once

#include "Interval.hpp"
#include "Vector.hpp"
#include <iostream>

using Color = Vector3;

inline void WriteColor(std::ostream& out, const Color& color)
{
    static const Interval intensity(0, 1);
    int r = intensity.clamp(color.x()) * 255;
    int g = intensity.clamp(color.y()) * 255;
    int b = intensity.clamp(color.z()) * 255;
    out << r << ' ' << g << ' ' << b << '\n';
}
