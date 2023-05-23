#pragma once
#include "vec/vec3.hpp"
#include "ray.hpp"
#include "IHittbale.hpp"
namespace mortal
{
    class Sphere : public IHittbale{
    public:
        Sphere(const Point3& center, float radius, std::shared_ptr<Material> material);
        bool IsIntersectionRay(const Ray& ray);
        bool HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) override;
    public:
        Point3 m_Center;
        std::shared_ptr<Material> m_Material;
        float m_Radius;
    };
    //96-1-1005
} // namespace mortal
