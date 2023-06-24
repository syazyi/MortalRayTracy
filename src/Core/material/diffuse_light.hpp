#pragma once
#include "material.hpp"
#include "texture/texture.hpp"
namespace mortal
{
    class DiffuseLight : public Material {
    public:
        DiffuseLight(const Color& c);
        DiffuseLight(std::shared_ptr<Texture> p);

        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut);
        virtual Color Emitted(double u, double v, const Point3& p) const;
    private:
        std::shared_ptr<Texture> m_Emit;
    };

} // namespace mortal
