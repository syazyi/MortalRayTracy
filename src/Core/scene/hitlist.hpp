#pragma once
#include "geometry/ray.hpp"
#include "geometry/IHittbale.hpp"
#include <memory>
#include <vector>
namespace mortal
{
    class HitList : public IHittbale {
    public:
        HitList() = default;
        void Add(std::shared_ptr<IHittbale> object);
        void Clear();
        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const  override;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const override;
    public:
        std::vector<std::shared_ptr<IHittbale>> m_Objects;
    };
    
} // namespace mortal
