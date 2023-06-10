#pragma once
#include "material.hpp"
#include "texture/solid.hpp"
namespace mortal
{
    class LambertianWithTexture : public Material {
    public:
        explicit LambertianWithTexture(const Color& attenation);
        explicit LambertianWithTexture(const std::shared_ptr<Texture> ptr);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    public:
        std::shared_ptr<Texture> m_Albedo;
    };

} // namespace mortal