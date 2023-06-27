#include "material.hpp"

namespace mortal
{
	bool Material::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& albedo, Ray& rayOut, double& pdf)
	{
		return false;
	}
	double Material::ScatterPDF(const Ray& rayIn, const HitResult& hitInfo, const Ray& RayOut)
	{
		return 0.0;
	}
	Color Material::Emitted(double u, double v, const Point3 &p) const
    {
        return Color(0.0, 0.0, 0.0);
    }


	bool MaterialDefault::Scatter(const Ray& rayIn, const HitResult& hitInfo, Color& attenuation, Ray& rayOut) {
		attenuation = Color(0.0, 0.0, 0.0);
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
