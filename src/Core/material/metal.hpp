#pragma once
#include "material.hpp"
namespace mortal
{
    class Metal : public Material {
    public:
        explicit Metal(const Color& albedo, float fuzzy = 1.0f);
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    public:
        Color m_Albedo;
        float m_Fuzzy;
    };

    
} // namespace mortal
