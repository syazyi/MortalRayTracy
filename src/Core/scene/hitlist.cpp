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
	bool HitList::HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) const
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

	bool HitList::AxisAlignBoundBox(float time0, float time1, AABB& aabb) const
	{
		if (m_Objects.empty()) {
			return false;
		}

		AABB outAABB;
		AABB tempAABB;
		for (auto& object : m_Objects) {
			if (!object->AxisAlignBoundBox(time0, time1, tempAABB)) {
				return false;
			}
			outAABB = outAABB + tempAABB;
		}
		aabb = outAABB;
		return true;
	}
} // namespace mortal
