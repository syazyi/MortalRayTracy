#pragma once
#include "geometry/ray.hpp"
#include "geometry/IHittbale.hpp"
#include <map>
#include <string>
#include <memory>
namespace mortal
{
    struct HitResult;
    class Material {
    public:
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& albedo, Ray& rayOut) = 0;
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& albedo, Ray& rayOut, double& pdf);
        virtual double ScatterPDF(const Ray& rayIn, const HitResult& hitInfo, const Ray& RayOut);
        virtual Color Emitted(double u, double v, const Point3& p) const;
        ~Material() {};
    };

    class MaterialDefault : public Material {
    public:
        MaterialDefault() = default;
        virtual bool Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) override;
    };

    class MaterialManagement {
    public:
        MaterialManagement();

        void Add(const std::string& name, std::shared_ptr<Material> material);
        std::shared_ptr<Material> Get(const std::string& name);
    private:
        std::map<std::string, std::shared_ptr<Material>> m_Materials;
    };
} // namespace mortal
