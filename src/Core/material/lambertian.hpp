#pragma once
#include "material.hpp"
namespace mortal
{
    class Lambertian : public Material {
    public:
        explicit Lambertian(const Color& attenation);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    public:
        Color m_Albedo;
    };
    
} // namespace mortal
