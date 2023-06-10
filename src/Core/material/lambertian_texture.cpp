#include "lambertian_texture.hpp"

namespace mortal
{
    
    LambertianWithTexture::LambertianWithTexture(const Color& attenation) : m_Albedo(std::make_shared<SolidTexture>(attenation))
    {

    }

    LambertianWithTexture::LambertianWithTexture(const std::shared_ptr<Texture> ptr) : m_Albedo(ptr)
    {

    }

    bool LambertianWithTexture::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
    {
        auto rayOutDir = hitInfo.normal + SampleUnitSphere();
        if (rayOutDir.NearZero()) {
            rayOutDir = hitInfo.normal;
        }
        rayOut = Ray(hitInfo.position, rayOutDir, rayIn.time);
        attenuation = m_Albedo->TextureSample(hitInfo.u, hitInfo.v, hitInfo.position);
        return true;
    }

} // namespace mortal
