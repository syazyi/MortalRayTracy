#include "plane.hpp"

namespace mortal
{   
    Plane::Plane(double p1, double p2, double p3, double p4, double k, PlaneCategory category, std::shared_ptr<Material> mptr) :m_P11(p1), m_P12(p2), m_P21(p3), m_P22(p4), m_K(k), m_Category(category), m_Material(mptr)
    {

    }

    bool Plane::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
    {
        double t = 0.0;
        double p1 = 0.0;
        double p2 = 0.0;
        Vec3 p;
        switch (m_Category)
        {
        case mortal::PlaneCategory::EXY:
         {
            t = (m_K - ray.original.z) / ray.direction.z;
            p = ray.at(t);
            p1 = p.x;
            p2 = p.y;
            hitResult.normal = Vec3(0.0, 0.0, 1.0);
         }
        break;
        case mortal::PlaneCategory::EYZ:
         {
            t = (m_K - ray.original.x) / ray.direction.x;
            p = ray.at(t);
            p1 = p.y;
            p2 = p.z;
            hitResult.normal = Vec3(1.0, 0.0, 0.0);
         }
        break;
        case mortal::PlaneCategory::EXZ:
        {
            t = (m_K - ray.original.y) / ray.direction.y;
            p = ray.at(t);
            p1 = p.x;
            p2 = p.z;
            hitResult.normal = Vec3(0.0, 1.0, 0.0);
        }
        break;
        }

        if (t < tMin || t > tMax) {
            return false;
        }

        if (p1 < m_P11 || p1 > m_P21 || p2 < m_P12 || p2 > m_P22) {
            return false;
        }

        hitResult.position = p;
        hitResult.material = m_Material.get();
        hitResult.frontFace = Dot(ray.direction, hitResult.normal) < 0.0;
        if (!hitResult.frontFace) {
            hitResult.normal = -hitResult.normal;
        }
        hitResult.t = t;
        hitResult.u = (p1 - m_P11) / (m_P21 - m_P11);
        hitResult.v = (p2 - m_P12) / (m_P22 - m_P12);
        return true;
    }

    bool Plane::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
    {
        switch (m_Category)
        {
        case mortal::PlaneCategory::EXY:
            aabb = AABB(Point3(m_P11, m_P12, m_K- 0.0001), Point3(m_P21, m_P22, m_K + 0.0001));
            return true;
        case mortal::PlaneCategory::EYZ:
            aabb = AABB(Point3(m_K - 0.0001, m_P11, m_P12), Point3(m_K - 0.0001, m_P21, m_P22));
            return true;
        case mortal::PlaneCategory::EXZ:
            aabb = AABB(Point3(m_P11, m_K - 0.0001, m_P12), Point3(m_P21, m_K - 0.0001, m_P22));
            return true;
        }
    }

    double Plane::PDFValue(const Point3& shaderpoint, const Vec3& vec) const
    {
        HitResult hitResult;
        if (!this->HitIntersectionRay(Ray(shaderpoint, vec), 0.001, Infinity, hitResult)) {
            return 0.0;
        }

        auto area = (m_P21 - m_P11) * (m_P22 - m_P12);
        auto cossine = fabs(Dot(hitResult.normal, Normal(vec)));
        auto distance = (hitResult.position - shaderpoint).Module();
        distance = distance * distance;
        return distance / (area * cossine);
    }

    Vec3 Plane::Random(const Point3& shaderpoint) const
    {
        if (m_Category == PlaneCategory::EXZ)
        {
            return Vec3(KRandom(m_P11, m_P21), m_K, KRandom(m_P12, m_P22)) - shaderpoint;
        }
        return Vec3();
    }



} // namespace mortal
