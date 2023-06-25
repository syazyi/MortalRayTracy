#include "constant_medium.hpp"
#include "material/isotropic.hpp"
namespace mortal
{
    
    ConstantMedium::ConstantMedium(std::shared_ptr<IHittbale> b, double neg_inv_density, const Color& c) : m_Boundary(b), m_NegInvDensity(1.0 / neg_inv_density), 
        m_Material(std::make_shared<Isotropic>(c))
    {
    }

    ConstantMedium::ConstantMedium(std::shared_ptr<IHittbale> b, double neg_inv_density, std::shared_ptr<Material> mPtr) : m_Boundary(b), m_NegInvDensity(1.0 / neg_inv_density),
        m_Material(mPtr)
    {
    }

    bool ConstantMedium::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
    {
        HitResult hitPoint1;
        HitResult hitPoint2;

        if (!m_Boundary->HitIntersectionRay(ray, -Infinity, Infinity, hitPoint1)) {
            return false;
        }
        if (!m_Boundary->HitIntersectionRay(ray, hitPoint1.t + 0.0001, Infinity, hitPoint2)) {
            return false;
        }

        if (hitPoint1.t < tMin) {
            hitPoint1.t = tMin;
        }
        if (hitPoint2.t > tMax) {
            hitPoint2.t = tMax;
        }

        if (hitPoint1.t >= hitPoint2.t)
        {
            return false;
        }

        if (hitPoint1.t < 0) {
            hitPoint1.t = 0;
        }

        auto ray_length = ray.direction.Module();
        auto distance_inside_boundary = (hitPoint2.t - hitPoint1.t) * ray_length;
        auto hit_distance = m_NegInvDensity * log(KRandom());

        if (hit_distance > distance_inside_boundary)
            return false;
        hitResult.t = hitPoint1.t + hit_distance / ray_length;
        hitResult.position = ray.at(hitResult.t);
        hitResult.normal = Vec3(1.0, 0.0, 0.0);
        hitResult.frontFace = true;
        hitResult.material = m_Material.get();

        return true;
    }

    bool ConstantMedium::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
    {
        m_Boundary->AxisAlignBoundBox(time0, time1, aabb);
        return true;
    }

} // namespace mortal
