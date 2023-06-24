#include "AABB.hpp"

namespace mortal
{
	AABB::AABB()
	{
		m_Top = Point3(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
		m_Bottom = Point3(std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
	}
	AABB::AABB(const Point3& top, const Point3& bottom) : m_Top(top), m_Bottom(bottom)
	{

	}

	bool AABB::BeHit(const Ray& ray, double t_min, double t_max) const
	{
		return TutorialHitFunc(ray, t_min, t_max);
	}

	EAxis AABB::GetLongestAxis()
	{
		auto X = abs(m_Top.x - m_Bottom.x);
		auto Y = abs(m_Top.y - m_Bottom.y);
		auto Z = abs(m_Top.z - m_Bottom.z);

		if (X > Y) {
			if (X > Z) {
				return EAxis::eX;
			}
			else {
				return EAxis::eZ;
			}
		}
		else {
			if (Y > Z) {
				return EAxis::eY;
			}
			else {
				return EAxis::eZ;
			}
		}
	}

	double AABB::GetAxisLength(EAxis axis)
	{
		switch (axis)
		{
		case mortal::EAxis::eX:
			return abs(m_Top.x - m_Bottom.x);
			break;
		case mortal::EAxis::eY:
			return abs(m_Top.y - m_Bottom.y);
			break;
		case mortal::EAxis::eZ:
			return abs(m_Top.z - m_Bottom.z);
			break;
		}
	}

	bool AABB::StandardHitFunc(const Ray& ray, double t_min, double t_max) const
	{
		return false;
	}

	bool AABB::TutorialHitFunc(const Ray& ray, double t_min, double t_max) const
	{
		for (int i = 0; i < 3; i++) {
			double div = 1.0 / ray.direction[i];
			double t0 = fminf((m_Top[i] - ray.original[i]) * div, (m_Bottom[i] - ray.original[i]) * div);
			double t1 = fmaxf((m_Top[i] - ray.original[i]) * div, (m_Bottom[i] - ray.original[i]) * div);
			if (div < 0.0) {
				std::swap(t0, t1);
			}
			t_min = t0 > t_min ? t0 : t_min;
			t_max = t1 < t_max ? t1 : t_max;
			if (t_max <= t_min) {
				return false;
			}
		}
		return true;
	}

	AABB operator+(const AABB& left, const AABB& right)
	{
		AABB aabb(
			Point3(
				fminf(left.m_Top.x, right.m_Top.x),
				fminf(left.m_Top.y, right.m_Top.y), 
				fminf(left.m_Top.z, right.m_Top.z)
			),
			Point3(
				fmaxf(left.m_Bottom.x, right.m_Bottom.x),
				fmaxf(left.m_Bottom.y, right.m_Bottom.y),
				fmaxf(left.m_Bottom.z, right.m_Bottom.z)
			)
		);
		return aabb;
	}
} // namespace mortal
