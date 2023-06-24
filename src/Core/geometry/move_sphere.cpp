#include "move_sphere.hpp"

namespace mortal
{
	MoveSphere::MoveSphere(const Point3& center0, const Point3& center1, double time0, double time1, double radius, std::shared_ptr<Material> material) : 
		m_Center0(center0), m_Center1(center1), m_Time0(time0), m_Time1(time1), m_Radius(radius), m_Material(material)
	{

	}

	bool MoveSphere::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
	{
        auto OmC = ray.original - GetRealCenter(ray.time);
        //vec(d)^2 * t^2 + 2 * vec(omc) * vec(d) * t + vec(omc)^2 - r^2;
        //double b = 2.f * Dot(OmC, ray.direction);
        double h = Dot(OmC, ray.direction);
        double a = ray.direction.ModuleSquare();
        double c = OmC.ModuleSquare() - m_Radius * m_Radius;
        double delta = h * h - a * c;
        if (delta >= 0.0) {
            hitResult.t = (-h - KSqrt(delta)) / a;
            if (hitResult.t < tMin || hitResult.t > tMax) {
                hitResult.t = (-h + KSqrt(delta)) / a;
                if (hitResult.t < tMin || hitResult.t > tMax) {
                    return false;
                }
            }
            hitResult.position = ray.at(hitResult.t);
            //if radius < 0.0 normal will be change.
            hitResult.normal = (hitResult.position - GetRealCenter(ray.time)) / m_Radius;
            auto dir_n = Dot(ray.direction, hitResult.normal);
            hitResult.frontFace = dir_n < 0.0;
            hitResult.material = m_Material.get();
            if (!hitResult.frontFace) {
                hitResult.normal = -hitResult.normal;
            }
            return true;
        }
        return false;
	}

    bool MoveSphere::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
    {
        AABB aabb0 = AABB(GetRealCenter(time0) + Vec3(m_Radius, m_Radius, m_Radius), GetRealCenter(time0) - Vec3(m_Radius, m_Radius, m_Radius));
        AABB aabb1 = AABB(GetRealCenter(time1) + Vec3(m_Radius, m_Radius, m_Radius), GetRealCenter(time1) - Vec3(m_Radius, m_Radius, m_Radius));
        aabb = aabb0 + aabb1;
        return true;
    }

	Point3 MoveSphere::GetRealCenter(double time) const
	{
		return m_Center0 + (time - m_Time0) / (m_Time1 - m_Time0) * (m_Center1 - m_Center0);
	}


} // namespace mortal
