#pragma once 
#include "IHittbale.hpp"
#include "plane.hpp"
#include "material/material.hpp"
#include "scene/hitlist.hpp"
namespace mortal
{
    class Box : public IHittbale{
    public:
        Box() = default;
        Box(const Point3& bottom, const Point3& top, std::shared_ptr<Material> mPtr);

        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const;
    private:
        Point3 m_BoxBottom;
        Point3 m_BoxTop;
        std::shared_ptr<Material> m_Material;
        HitList m_HitObjects;
    };

} // namespace mortal
