#include "light_pdf.hpp"

namespace mortal
{

    LightPDF::LightPDF(std::shared_ptr<IHittbale> object, const Point3& shaderpoint) : m_HitObject(object), m_ShaderPoint(shaderpoint)
    {
    }

    double LightPDF::Value(const Vec3& dir) const
    {
        return m_HitObject->PDFValue(m_ShaderPoint, dir);
    }

    Vec3 LightPDF::Generate() const
    {
        return m_HitObject->Random(m_ShaderPoint);
    }

} // namespace mortal
