#pragma once 
#include "ray.hpp"
namespace mortal
{
    enum class EAxis
    {
        eX,
        eY,
        eZ
    };

    class AABB{
    public:
        AABB();
        AABB(const Point3& top, const Point3& bottom);

        bool BeHit(const Ray& ray, double t_min, double t_max) const;

        EAxis GetLongestAxis();
        double GetAxisLength(EAxis axis);

        Point3 m_Top;
        Point3 m_Bottom;
    private:
        bool StandardHitFunc(const Ray& ray, double t_min, double t_max) const;
        bool TutorialHitFunc(const Ray& ray, double t_min, double t_max) const;
    };

    AABB operator+(const AABB& left, const AABB& right);

} // namespace mortal
