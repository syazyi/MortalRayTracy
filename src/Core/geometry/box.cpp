#include "box.hpp"

namespace mortal
{
    Box::Box(const Point3& bottom, const Point3& top, std::shared_ptr<Material> mPtr) : m_BoxBottom(bottom), m_BoxTop(top), m_Material(mPtr)
    {
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.x, m_BoxBottom.y, m_BoxTop.x, m_BoxTop.y, m_BoxBottom.z, PlaneCategory::EXY, m_Material));
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.x, m_BoxBottom.y, m_BoxTop.x, m_BoxTop.y, m_BoxTop.z, PlaneCategory::EXY, m_Material));
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.x, m_BoxBottom.z, m_BoxTop.x, m_BoxTop.z, m_BoxBottom.y, PlaneCategory::EXZ, m_Material));
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.x, m_BoxBottom.z, m_BoxTop.x, m_BoxTop.z, m_BoxTop.y, PlaneCategory::EXZ, m_Material));
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.y, m_BoxBottom.z, m_BoxTop.y, m_BoxTop.z, m_BoxBottom.x, PlaneCategory::EYZ, m_Material));
        m_HitObjects.Add(std::make_shared<Plane>(m_BoxBottom.y, m_BoxBottom.z, m_BoxTop.y, m_BoxTop.z, m_BoxTop.x, PlaneCategory::EYZ, m_Material));
    }

    bool Box::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
    {
        return m_HitObjects.HitIntersectionRay(ray, tMin, tMax, hitResult);
    }

    bool Box::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
    {
        aabb = AABB(m_BoxBottom, m_BoxTop);
        return true;
    }

} // namespace mortal
