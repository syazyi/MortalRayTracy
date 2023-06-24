#pragma once 
#include "math/vec/color.hpp"
namespace mortal
{
    class Texture {
    public:
        virtual Color TextureSample(double u, double v, const Point3& p) const = 0;
    };
} // namespace mortal
