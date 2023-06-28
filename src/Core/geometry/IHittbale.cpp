#include "IHittbale.hpp"

namespace mortal
{
    double IHittbale::PDFValue(const Point3& shaderpoint, const Vec3& vec) const
    {
        return 0.0;
    }
    Vec3 IHittbale::Random(const Point3& shaderpoint) const
    {
        return Vec3();
    }
} // namespace mortal


