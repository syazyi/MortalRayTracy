#include "material.hpp"

namespace mortal
{
		
    Color Material::Emitted(float u, float v, const Point3 &p) const
    {
        return Color(0.0f, 0.0f, 0.0f);
    }


	bool MaterialDefault::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) {
		attenuation = Color(0.0f, 0.0f, 0.0f);
		return true;
	}

	MaterialManagement::MaterialManagement() {
		m_Materials.emplace("Default", std::make_shared<MaterialDefault>());
	}
	
	void MaterialManagement::Add(const std::string& name, std::shared_ptr<Material> material) {
		m_Materials.emplace(name, material);
	}

	std::shared_ptr<Material> MaterialManagement::Get(const std::string& name)
	{
		return m_Materials.find(name)->second;
	}

} // namespace mortal
