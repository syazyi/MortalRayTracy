#pragma once 
#include "IHittbale.hpp"
#include "material/material.hpp"
namespace mortal
{ 
    enum class PlaneCategory
    {
        EXY,
        EYZ,
        EXZ
    };

    class Plane : public IHittbale{
    public:
        Plane() = default;
        Plane(double p1, double p2, double p3, double p4, double k, PlaneCategory category, std::shared_ptr<Material> mptr);
        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const;
        virtual double PDFValue(const Point3& shaderpoint, const Vec3& vec) const override;
        virtual Vec3 Random(const Point3& shaderpoint) const override;
    private:
        std::shared_ptr<Material> m_Material;
        //point1 x0, y0
        double m_P11, m_P12;
        //point2 x1, y1
        double m_P21, m_P22;
        double m_K;
        PlaneCategory m_Category;
    };


} // namespace mortal
