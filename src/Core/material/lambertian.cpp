#include "lambertian.hpp"
namespace mortal
{
	Lambertian::Lambertian(const Color& attenation) : m_Albedo(attenation)
	{
	}
	bool Lambertian::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
	{
		Vec3 rayOutDir;
		while (1)
		{
			rayOutDir = SampleUnitSphere();
			if (Dot(hitInfo.normal, rayOutDir) > 0.0f) {
				break;
			}
		}

		/*auto rayOutDir = hitInfo.normal + SampleUnitSphere();
		if (rayOutDir.NearZero()) {
			rayOutDir = hitInfo.normal;
		}*/
		rayOut = Ray(hitInfo.position, rayOutDir, rayIn.time);
		attenuation = m_Albedo;
		return true;
	}

} // namespace mortal
