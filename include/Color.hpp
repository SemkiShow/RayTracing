#pragma once

#include "Vector.hpp"
#include <iostream>

using Color = Vector3;

inline void WriteColor(std::ostream& out, const Color& color)
{
    out << floor(color.x() * 255) << ' ' << floor(color.y() * 255) << ' ' << floor(color.z() * 255)
        << '\n';
}
