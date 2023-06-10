#pragma once
#include "texture.hpp"
namespace mortal
{
    class CheckTexture : public Texture{
    public:
        CheckTexture();
        virtual Color TextureSample(float u, float v, const Point3& p) const override;

    private:
        std::shared_ptr<Texture> m_OddTexture;
        std::shared_ptr<Texture> m_EvenTexture;
    };


} // namespace mortal
