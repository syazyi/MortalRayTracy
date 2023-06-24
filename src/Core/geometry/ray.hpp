#pragma once
#include "vec/vec3.hpp"
namespace mortal
{
    class Ray{
    public:
        Point3 original;
        Vec3 direction;
        double time{ 0.0 }; // add move blur
    public:
        Ray() = default;
        Ray(const Point3& _orig, const Vec3& _dir, double _time);

        Vec3 at(double t) const;
    };
} // namespace mortal
