#include "dielectric.hpp"

namespace mortal
{
    Dielectric::Dielectric(double refraction) : m_RefractiveIndex(refraction)
    {

    }

    bool Dielectric::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
    {
        attenuation = Color(1.0, 1.0, 1.0);
        //if from inside to outside , RefractiveIndex shoulde be constracted.
        auto refractive = m_RefractiveIndex;
        if (hitInfo.frontFace) {
            refractive = 1.0 / refractive;
        }
        auto cosTheta = fmin(fmax(Dot(-rayIn.direction, hitInfo.normal), 0.0), 1.0);
        auto sinTheta = KSqrt(1.0 - cosTheta * cosTheta);
        Vec3 rayOutDir;
        if ((sinTheta * refractive) > 1.0 || Reflectance(cosTheta, refractive) > KRandom()) {
            rayOutDir = Reflect(rayIn.direction, hitInfo.normal);
        }
        else {
            rayOutDir = Refract(rayIn.direction, hitInfo.normal, refractive);
        }
        rayOut = Ray(hitInfo.position, rayOutDir, rayIn.time);
        return true;
    }

    double Dielectric::Reflectance(double cosine, double refractiveIndex)
    {
        auto R0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
        R0 = R0 * R0;
        return R0 + (1.0 - R0) * pow((1.0 - cosine), 5);
    }

} // namespace mortal

