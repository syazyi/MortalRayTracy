#include "ray.hpp"
namespace mortal
{
    Ray::Ray(const Point3& _orig, const Vec3& _dir, double _time) : original(_orig), direction(_dir), time(_time){
        direction.NormalLize();
    }

    Vec3 Ray::at(double t) const{
        return original + t * direction;
    }
} // namespace mortal
