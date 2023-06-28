#pragma once
#include "pdf/pdf.hpp"
#include "geometry/IHittbale.hpp"
namespace mortal
{
    class LightPDF : public PDF{
    public:
        LightPDF() = default;
        LightPDF(std::shared_ptr<IHittbale> object, const Point3& shaderpoint);

        virtual double Value(const Vec3& dir) const override;
        virtual Vec3 Generate() const override;
    private:
        std::shared_ptr<IHittbale> m_HitObject;
        Point3 m_ShaderPoint;
    };


} // namespace mortal