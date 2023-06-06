#include "AABB.hpp"

namespace mortal
{
	AABB::AABB(const Point3& top, const Point3& bottom) : m_Top(top), m_Bottom(bottom)
	{

	}

	bool AABB::BeHit(Ray& ray, float t_min, float t_max)
	{
		return TutorialHitFunc(ray, t_min, t_max);
	}

	bool AABB::StandardHitFunc(Ray& ray, float t_min, float t_max)
	{
		return false;
	}

	bool AABB::TutorialHitFunc(Ray& ray, float t_min, float t_max)
	{
		for (int i = 0; i < 3; i++) {
			float t0 = fminf((m_Top[i] - ray.original[i]) / ray.direction[i], (m_Bottom[i] - ray.original[i]) / ray.direction[i]);
			float t1 = fmaxf((m_Top[i] - ray.original[i]) / ray.direction[i], (m_Bottom[i] - ray.original[i]) / ray.direction[i]);
			t_min = fmaxf(t0, t_min);
			t_max = fminf(t1, t_max);
			if (t_max <= t_min) {
				return false;
			}
		}
		return true;
	}
} // namespace mortal
