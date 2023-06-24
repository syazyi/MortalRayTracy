#pragma once 
#include "texture.hpp"
namespace mortal
{
    class SolidTexture : public Texture{
    public:
        SolidTexture() = default;
        SolidTexture(const Color& color);
        SolidTexture(double r, double g, double b);

        virtual Color TextureSample(double u, double v, const Point3& p) const override;
    private:
        Color m_ColorValue;
    };


} // namespace mortal
