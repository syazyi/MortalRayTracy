#pragma once 
#include "IHittbale.hpp"
#include "material/material.hpp"
namespace mortal
{
    class ConstantMedium : public IHittbale{
    public:
        ConstantMedium(std::shared_ptr<IHittbale> b, double neg_inv_density, const Color& c);
        ConstantMedium(std::shared_ptr<IHittbale> b, double neg_inv_density, std::shared_ptr<Material> mPtr);

        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const;
    private:
        std::shared_ptr<IHittbale> m_Boundary;
        double m_NegInvDensity;
        std::shared_ptr<Material> m_Material;
    };


} // namespace mortal
