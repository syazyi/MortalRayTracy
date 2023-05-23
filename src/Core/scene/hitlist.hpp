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
        virtual bool HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) override;
    private:
        std::vector<std::shared_ptr<IHittbale>> m_Objects;
    };
    
} // namespace mortal
