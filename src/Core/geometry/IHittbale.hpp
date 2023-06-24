#pragma once
#include "math/vec/vec3.hpp"
#include "geometry/ray.hpp"
#include "material/material.hpp"
#include "AABB.hpp"
namespace mortal
{
    class Material;
    struct HitResult
    {
        Point3 position;
        Point3 normal;
        Material* material;
        double t;
        double u;
        double v;
        bool frontFace;
    };

    class IHittbale {
    public:
        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const = 0;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const = 0;
    };
} // namespace mortal
