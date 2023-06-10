#include "solid.hpp"

namespace mortal
{
    SolidTexture::SolidTexture(const Color& color) : m_ColorValue(color)
    {

    }
    SolidTexture::SolidTexture(float r, float g, float b) : m_ColorValue(r, g, b)
    {

    }
    Color SolidTexture::TextureSample(float u, float v, const Point3& p) const
    {
        return m_ColorValue;
    }
} // namespace mortal
