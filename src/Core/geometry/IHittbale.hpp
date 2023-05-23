#pragma once
#include "math/vec/vec3.hpp"
#include "geometry/ray.hpp"
#include "material/material.hpp"
namespace mortal
{
    class Material;
    struct HitResult
    {
        Point3 position;
        Point3 normal;
        Material* material;
        float t;
        bool frontFace;
    };

    class IHittbale {
    public:
        virtual bool HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) = 0;
    };
} // namespace mortal
