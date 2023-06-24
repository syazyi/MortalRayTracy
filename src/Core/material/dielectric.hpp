#pragma once
#include "material.hpp"
namespace mortal
{
    class Dielectric : public Material {
    public:
        Dielectric(double refraction);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    private:
        double Reflectance(double cosine, double refractiveIndex);
    private:
        double m_RefractiveIndex;
    };

    
} // namespace mortal
