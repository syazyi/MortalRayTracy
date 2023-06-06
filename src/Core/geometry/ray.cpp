#include "ray.hpp"
namespace mortal
{
    Ray::Ray(const Point3& _orig, const Vec3f& _dir, float _time) : original(_orig), direction(_dir), time(_time){
        direction.NormalLize();
    }

    Vec3f Ray::at(float t) const{
        return original + t * direction;
    }
} // namespace mortal
