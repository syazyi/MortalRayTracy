#pragma once
#include "vec/vec3.hpp"
#include "ray.hpp"
#include "IHittbale.hpp"
namespace mortal
{
    class Sphere : public IHittbale{
    public:
        Sphere(const Point3& center, double radius, std::shared_ptr<Material> material);
        bool IsIntersectionRay(const Ray& ray);
        bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const override;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const  override;

    public:
        Point3 m_Center;
        std::shared_ptr<Material> m_Material;
        double m_Radius;
    private:
        static void GetSphereUV(const Point3& p, double& u, double& v);
    };
} // namespace mortal
