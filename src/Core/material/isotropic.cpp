#include "isotropic.hpp"
#include "texture/solid.hpp"
namespace mortal
{
	Isotropic::Isotropic(const Color& color) : m_Albedo(std::make_shared<SolidTexture>(color))
	{

	}

	bool Isotropic::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut)
	{
		rayOut = Ray(hitInfo.position, SampleUnitSphere(), rayIn.time);
		attenuation = m_Albedo->TextureSample(hitInfo.u, hitInfo.v, hitInfo.position);
		return true;
	}
} // namespace mortal
