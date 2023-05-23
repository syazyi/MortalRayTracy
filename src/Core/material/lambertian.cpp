#include "lambertian.hpp"
namespace mortal
{
	Lambertian::Lambertian(const Color& attenation) : m_Albedo(attenation)
	{
	}
	bool Lambertian::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
	{
		auto rayOutDir = hitInfo.normal + SampleUnitSphere();
		if (rayOutDir.NearZero()) {
			rayOutDir = hitInfo.normal;
		}
		rayOut = Ray(hitInfo.position, rayOutDir);
		attenuation = m_Albedo;
		return true;
	}

} // namespace mortal
