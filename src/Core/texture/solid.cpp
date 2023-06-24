#include "solid.hpp"

namespace mortal
{
    SolidTexture::SolidTexture(const Color& color) : m_ColorValue(color)
    {

    }
    SolidTexture::SolidTexture(double r, double g, double b) : m_ColorValue(r, g, b)
    {

    }
    Color SolidTexture::TextureSample(double u, double v, const Point3& p) const
    {
        return m_ColorValue;
    }
} // namespace mortal
