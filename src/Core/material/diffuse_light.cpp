#include "diffuse_light.hpp"
#include "texture/solid.hpp"
namespace mortal
{

    DiffuseLight::DiffuseLight(const Color &c) : m_Emit(std::make_shared<SolidTexture>(c))
    {

    }

    DiffuseLight::DiffuseLight(const std::shared_ptr<Texture> p) : m_Emit(p)
    {

    }

    bool DiffuseLight::Scatter(const Ray &rayIn, const HitResult &hitInfo, Color &attenuation, Ray &rayOut)
    {
        return false;
    }

    Color DiffuseLight::Emitted(double u, double v, const Point3 &p) const
    {
        return m_Emit->TextureSample(u, v, p);
    }

} // namespace mortal
