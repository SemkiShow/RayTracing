#pragma once

#include "Utils.hpp"
#include <algorithm>

class Interval
{
  public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {}

    Interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }
    bool contains(double x) const { return min <= x && x <= max; }
    bool surrounds(double x) const { return min < x && x < max; }
    double clamp(double x) const { return std::max(min, std::min(max, x)); }

    static const Interval empty, universe;
};
