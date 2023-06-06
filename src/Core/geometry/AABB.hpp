#pragma once 
#include "ray.hpp"
namespace mortal
{
    class AABB{
    public:
        AABB() = default;
        AABB(const Point3& top, const Point3& bottom);

        bool BeHit(Ray& ray, float t_min, float t_max);
    private:
        Point3 m_Top;
        Point3 m_Bottom;

        bool StandardHitFunc(Ray& ray, float t_min, float t_max);
        bool TutorialHitFunc(Ray& ray, float t_min, float t_max);
    };

} // namespace mortal
