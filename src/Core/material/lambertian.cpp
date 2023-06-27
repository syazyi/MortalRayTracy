#include "lambertian.hpp"
#include "base/ONB.hpp"
namespace mortal
{
	Lambertian::Lambertian(const Color& attenation) : m_Albedo(attenation)
	{
	}
	bool Lambertian::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
	{
		/*Vec3 rayOutDir;
		while (1)
		{
			rayOutDir = SampleUnitSphere();
			if (Dot(hitInfo.normal, rayOutDir) > 0.0f) {
				break;
			}
		}*/

		auto rayOutDir = hitInfo.normal + SampleUnitSphere();
		if (rayOutDir.NearZero()) {
			rayOutDir = hitInfo.normal;
		}
		rayOut = Ray(hitInfo.position, rayOutDir, rayIn.time);
		attenuation = m_Albedo;
		return true;
	}

	bool Lambertian::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& albedo, Ray& rayOut, double& pdf)
	{
		/*auto rayOutDir = hitInfo.normal + SampleUnitSphere();
		if (rayOutDir.NearZero()) {
			rayOutDir = hitInfo.normal;
		}*/
		//Vec3 rayOutDir;
		/*rayOutDir = SampleUnitSphere();
		if (Dot(hitInfo.normal, rayOutDir) < 0.0f) {
			rayOutDir = -rayOutDir;
		}*/

		ONB uvw;
		uvw.BuildFromW(hitInfo.normal);
		auto rayOutDir = uvw.local(SampleUnitSphere()).NormalLize();
		rayOut = Ray(hitInfo.position, rayOutDir, rayIn.time);
		albedo = m_Albedo;
		pdf = Dot(rayOut.direction, uvw.w) * OneDivPi;
		//pdf =  0.5 * OneDivPi;
		return true;
	}

	double Lambertian::ScatterPDF(const Ray& rayIn, const HitResult& hitInfo, const Ray& rayOut)
	{
		auto cosine = Dot(rayOut.direction, hitInfo.normal);
		return cosine < 0.0 ? 0.0 : cosine * OneDivPi;
	}

} // namespace mortal
