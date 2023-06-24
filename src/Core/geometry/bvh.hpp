#pragma once 
#include "IHittbale.hpp"
#include "AABB.hpp"
#include "scene/hitlist.hpp"
namespace mortal
{
    class BVHNode : public IHittbale{
    public:
        BVHNode() = default;
        BVHNode(const HitList& list, size_t start, size_t end, double time0, double time1);

        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const override;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const override;
    private:
        std::shared_ptr<IHittbale> m_Left;
        std::shared_ptr<IHittbale> m_Right;
        AABB m_Box;
    };


} // namespace moetal
