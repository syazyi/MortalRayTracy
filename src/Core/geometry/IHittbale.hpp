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
        float t;
        float u;
        float v;
        bool frontFace;
    };

    class IHittbale {
    public:
        virtual bool HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) const = 0;
        virtual bool AxisAlignBoundBox(float time0, float time1, AABB& aabb) const = 0;
    };
} // namespace mortal
