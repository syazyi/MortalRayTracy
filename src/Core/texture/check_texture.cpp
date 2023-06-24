#include "check_texture.hpp"
#include "solid.hpp"
namespace mortal
{
	CheckTexture::CheckTexture()
	{
		m_OddTexture = std::make_shared<SolidTexture>(Color(0.2f, 0.3f, 0.1f));
		m_EvenTexture = std::make_shared<SolidTexture>(Color(0.9f, 0.9f, 0.9f));
	}
	Color CheckTexture::TextureSample(double u, double v, const Point3& p) const
	{
		auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
		if (sines < 0) {
			return m_OddTexture->TextureSample(u, v, p);
		}
		else {
			return m_EvenTexture->TextureSample(u, v, p);
		}
	}
} // namespace mortal
