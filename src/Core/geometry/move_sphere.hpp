#pragma once
#include "IHittbale.hpp"
namespace mortal
{
    class MoveSphere : public IHittbale {
    public:
        MoveSphere() = default;
        MoveSphere(const Point3& center0, const Point3& center1, float time0, float time1, float radius, std::shared_ptr<Material> material);
        virtual bool HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) const override;
        virtual bool AxisAlignBoundBox(float time0, float time1, AABB& aabb) const override;
        Point3 GetRealCenter(float time) const;
    private:
        Point3 m_Center0;
        Point3 m_Center1;
        std::shared_ptr<Material> m_Material;
        float m_Time0;
        float m_Time1;
        float m_Radius;
    };
} // namespace mortal
