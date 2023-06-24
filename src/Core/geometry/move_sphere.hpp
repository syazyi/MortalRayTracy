#pragma once
#include "IHittbale.hpp"
namespace mortal
{
    class MoveSphere : public IHittbale {
    public:
        MoveSphere() = default;
        MoveSphere(const Point3& center0, const Point3& center1, double time0, double time1, double radius, std::shared_ptr<Material> material);
        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const override;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const override;
        Point3 GetRealCenter(double time) const;
    private:
        Point3 m_Center0;
        Point3 m_Center1;
        std::shared_ptr<Material> m_Material;
        double m_Time0;
        double m_Time1;
        double m_Radius;
    };
} // namespace mortal
