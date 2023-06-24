#pragma once 
#include "texture.hpp"

namespace mortal
{
    class ImageTexture : public Texture{
    public:
        ImageTexture() = default;
        ImageTexture(const char* filename);
        virtual Color TextureSample(double u, double v, const Point3& p) const;
    private:
        void* m_Data{ nullptr };
        int m_TextureWidth;
        int m_TextureHeight;
        int m_BytesPerScanline;
        constexpr static int BytesPerPixel = 3;
    };

} // namespace mortal
