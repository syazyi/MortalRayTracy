#pragma once 
#include "material.hpp"
#include "texture/texture.hpp"
namespace mortal
{
    class Isotropic : public Material{
    public:
        Isotropic(const Color& color);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut);
    private:
        std::shared_ptr<Texture> m_Albedo;
    };
} // namespace mortal
