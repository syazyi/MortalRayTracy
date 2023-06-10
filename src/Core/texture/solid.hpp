#pragma once 
#include "texture.hpp"
namespace mortal
{
    class SolidTexture : public Texture{
    public:
        SolidTexture() = default;
        SolidTexture(const Color& color);
        SolidTexture(float r, float g, float b);

        virtual Color TextureSample(float u, float v, const Point3& p) const override;
    private:
        Color m_ColorValue;
    };


} // namespace mortal
