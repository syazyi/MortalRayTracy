#include "sphere.hpp"
#include "math/base/calculate.hpp"
namespace mortal
{
    Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> material) : m_Center(center), m_Radius(radius), m_Material(material)
    {

    }

    bool Sphere::IsIntersectionRay(const Ray& ray)
    {
        auto OmC = ray.original - m_Center;
        //vec(d)^2 * t^2 + 2 * vec(omc) * vec(d) * t + vec(omc)^2 - r^2;
        //double b = 2.f * Dot(OmC, ray.direction);
        double h = Dot(OmC, ray.direction);
        double a = ray.direction.ModuleSquare();
        double c = OmC.ModuleSquare() - m_Radius * m_Radius;
        double delta = h * h - a * c;
        return (delta > 0.0);
    }

    bool Sphere::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
    {
        auto OmC = ray.original - m_Center;
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
                if (hitResult.t < tMin || hitResult.t > tMax){
                    return false;
                }
            }
            hitResult.position = ray.at(hitResult.t);
            //if radius < 0.0 normal will be change.
            hitResult.normal = (hitResult.position - m_Center) / m_Radius;
            auto dir_n = Dot(ray.direction, hitResult.normal);
            hitResult.frontFace = dir_n < 0.0;
            hitResult.material = m_Material.get();
            if (!hitResult.frontFace) {
                hitResult.normal = -hitResult.normal;
            }
            GetSphereUV(hitResult.normal, hitResult.u, hitResult.v);
            return true;
        }
        return false;
    }

    bool Sphere::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
    {
        aabb = AABB(m_Center + Vec3(m_Radius, m_Radius, m_Radius),
            m_Center - Vec3(m_Radius, m_Radius, m_Radius));
        return true;
    }

    void Sphere::GetSphereUV(const Point3& p, double& u, double& v)
    {
        auto theta = acos(-p.y);
        auto phi = atan2(-p.z, p.x) + Pi;

        u = phi * OneDiv2Pi;
        v = theta * OneDivPi;
    }
} // namespace mortal
