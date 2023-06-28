#include "cosine_pdf.hpp"

namespace mortal
{
    
    CosinePDF::CosinePDF(const Vec3& normal)
    {
        m_uvw.BuildFromW(normal);
    }

    double CosinePDF::Value(const Vec3& dir) const
    {
        auto cosine = Dot(Normal(dir), m_uvw.w);
        return (cosine <= 0) ? 0 : cosine * OneDivPi;
    }

    Vec3 CosinePDF::Generate() const
    {
        return m_uvw.local(SampleHemisphere());
    }

} // namespace mortal
