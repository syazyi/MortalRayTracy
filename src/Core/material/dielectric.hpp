#pragma once
#include "material.hpp"
namespace mortal
{
    class Dielectric : public Material {
    public:
        Dielectric(float refraction);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    private:
        float Reflectance(float cosine, float refractiveIndex);
    private:
        float m_RefractiveIndex;
    };

    
} // namespace mortal
