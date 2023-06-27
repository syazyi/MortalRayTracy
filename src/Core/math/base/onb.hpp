#pragma once
#include "vec/vec3.hpp"
namespace mortal
{
    class ONB {
    public:
        ONB() {}

        Vec3 local(double a, double b, double c) const {
            return a * u + b * v + c * w;
        }

        Vec3 local(const Vec3& a) const {
            return a.x * u + a.y * v + a.z * w;
        }

        void BuildFromW(const Vec3&);

    public:
        Vec3 u;
        Vec3 v;
        Vec3 w;
};
} // namespace mortal
