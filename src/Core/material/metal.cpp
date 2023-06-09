#include "metal.hpp"

namespace mortal
{
    Metal::Metal(const Color& albedo, double fuzzy) : m_Albedo(albedo), m_Fuzzy(fuzzy)
    {

    }

    bool Metal::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
    {
        rayOut = Ray(hitInfo.position, Reflect(rayIn.direction, hitInfo.normal) + m_Fuzzy * SampleUnitSphere(), rayIn.time);
        attenuation = m_Albedo;
        return Dot(rayOut.direction, hitInfo.normal) > 0.0;
    }

} // namespace mortal
