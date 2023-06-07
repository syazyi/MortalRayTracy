#include "sphere.hpp"
#include "math/base/calculate.hpp"
namespace mortal
{
    Sphere::Sphere(const Point3& center, float radius, std::shared_ptr<Material> material) : m_Center(center), m_Radius(radius), m_Material(material)
    {

    }

    bool Sphere::IsIntersectionRay(const Ray& ray)
    {
        auto OmC = ray.original - m_Center;
        //vec(d)^2 * t^2 + 2 * vec(omc) * vec(d) * t + vec(omc)^2 - r^2;
        //float b = 2.f * Dot(OmC, ray.direction);
        float h = Dot(OmC, ray.direction);
        float a = ray.direction.ModuleSquare();
        float c = OmC.ModuleSquare() - m_Radius * m_Radius;
        float delta = h * h - a * c;
        return (delta > 0.0f);
    }

    bool Sphere::HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) const
    {
        auto OmC = ray.original - m_Center;
        //vec(d)^2 * t^2 + 2 * vec(omc) * vec(d) * t + vec(omc)^2 - r^2;
        //float b = 2.f * Dot(OmC, ray.direction);
        float h = Dot(OmC, ray.direction);
        float a = ray.direction.ModuleSquare();
        float c = OmC.ModuleSquare() - m_Radius * m_Radius;
        float delta = h * h - a * c;
        if (delta >= 0.0f) {
            hitResult.t = (-h - KSqrt(delta)) / a;
            if (hitResult.t < tMin || hitResult.t > tMax) {
                hitResult.t = (-h + KSqrt(delta)) / a;
                if (hitResult.t < tMin || hitResult.t > tMax){
                    return false;
                }
            }
            hitResult.position = ray.at(hitResult.t);
            //if radius < 0.0f normal will be change.
            hitResult.normal = (hitResult.position - m_Center) / m_Radius;
            auto dir_n = Dot(ray.direction, hitResult.normal);
            hitResult.frontFace = dir_n < 0.0f;
            hitResult.material = m_Material.get();
            if (!hitResult.frontFace) {
                hitResult.normal = -hitResult.normal;
            }
            return true;
        }
        return false;
    }

    bool Sphere::AxisAlignBoundBox(float time0, float time1, AABB& aabb) const
    {
        aabb = AABB(m_Center + Vec3f(m_Radius, m_Radius, m_Radius),
            m_Center - Vec3f(m_Radius, m_Radius, m_Radius));
        return true;
    }
} // namespace mortal
