#pragma once
#include "material.hpp"
namespace mortal
{
    class Lambertian : public Material {
    public:
        explicit Lambertian(const Color& attenation);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& albedo, Ray& rayOut, double& pdf) override;
        virtual double ScatterPDF(const Ray& rayIn, const HitResult& hitInfo, const Ray& RayOut) override;
        virtual Vec3 BRDF(const Ray& rayIn, const HitResult& hitInfo, const Ray& RayOut);
    public:
        Color m_Albedo;
    };
    
} // namespace mortal
