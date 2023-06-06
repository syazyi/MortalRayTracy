#pragma once
#include "vec/vec3.hpp"
namespace mortal
{
    class Ray{
    public:
        Point3 original;
        Vec3f direction;
        float time{ 0.0f }; // add move blur
    public:
        Ray() = default;
        Ray(const Point3& _orig, const Vec3f& _dir, float _time);

        Vec3f at(float t) const;
    };
} // namespace mortal
