#include "dielectric.hpp"

namespace mortal
{
    Dielectric::Dielectric(float refraction) : m_RefractiveIndex(refraction)
    {

    }

    bool Dielectric::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
    {
        attenuation = Color(1.0f, 1.0f, 1.0f);
        //if from inside to outside , RefractiveIndex shoulde be constracted.
        auto refractive = m_RefractiveIndex;
        if (hitInfo.frontFace) {
            refractive = 1.0f / refractive;
        }
        auto cosTheta = fmin(fmax(Dot(-rayIn.direction, hitInfo.normal), 0.0f), 1.0f);
        auto sinTheta = KSqrt(1.0f - cosTheta * cosTheta);
        Vec3f rayOutDir;
        if ((sinTheta * refractive) > 1.0f || Reflectance(cosTheta, refractive) > KRandom()) {
            rayOutDir = Reflect(rayIn.direction, hitInfo.normal);
        }
        else {
            rayOutDir = Refract(rayIn.direction, hitInfo.normal, refractive);
        }
        rayOut = Ray(hitInfo.position, rayOutDir);
        return true;
    }

    float Dielectric::Reflectance(float cosine, float refractiveIndex)
    {
        auto R0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
        R0 = R0 * R0;
        return R0 + (1.0f - R0) * pow((1.0f - cosine), 5);
    }

} // namespace mortal

