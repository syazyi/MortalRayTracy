#include "hitlist.hpp"
namespace mortal
{
	void HitList::Add(std::shared_ptr<IHittbale> object)
	{
		m_Objects.emplace_back(object);
	}
	void HitList::Clear()
	{
		m_Objects.clear();
	}
	bool HitList::HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult)
	{
		HitResult temp;
		bool ret = false;
		auto closestFar = tMax;

		for (const auto& object : m_Objects) {
			if (object->HitIntersectionRay(ray, tMin, closestFar, temp)) {
				ret = true;
				closestFar = temp.t;
				hitResult = temp;
			}
		}
		return ret;
	}
} // namespace mortal