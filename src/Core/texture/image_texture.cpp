#include "image_texture.hpp"
#include "mrt_stb_image.hpp"
namespace mortal
{
    ImageTexture::ImageTexture(const char *filename)
    {
        auto components_per_pixel = BytesPerPixel;
        m_Data = stbi_load(filename, &m_TextureWidth, &m_TextureHeight, &components_per_pixel, components_per_pixel);
        if (!m_Data) {
            std::cerr << "ERROR: Could not load texture image file '" <<
            filename << "'.\n";
            m_TextureWidth = m_TextureHeight = 0;
        }
        m_BytesPerScanline = BytesPerPixel * m_TextureWidth;

    }

    Color ImageTexture::TextureSample(double u, double v, const Point3 &p) const
    {
        if(m_Data == nullptr){
            return Color(0.0, 1.0, 1.0);
        }
        
        u = Clamp(u, 0.0, 1.0);
        v = 1 - Clamp(v, 0.0, 1.0);

        auto i = static_cast<int>(u * m_TextureWidth);
        auto j = static_cast<int>(v * m_TextureHeight);

        //texture sample mode
        if (i >= m_TextureWidth) i = m_TextureWidth - 1;
        if (j >= m_TextureHeight) j = m_TextureHeight - 1;

        auto ColorScale = 1.0 / 255.0;

        auto pixel = reinterpret_cast<uint8_t*>(m_Data) + j * m_BytesPerScanline + i * BytesPerPixel;

        return Color(ColorScale * pixel[0], ColorScale * pixel[1], ColorScale * pixel[2] );
    }

} // namespace mortal
