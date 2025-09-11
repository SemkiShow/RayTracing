#pragma once

#include "Vector.hpp"
#include <iostream>

using Color = Vec3;

inline void WriteColor(std::ostream& out, const Color& color)
{
    out << color.x() * 255 << ' ' << color.y() * 255 << ' ' << color.z() * 255 << '\n';
}
