#include "vec3.hpp"
#include "base/calculate.hpp"
namespace mortal
{
    inline namespace math
    {

        Vec3::Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}
        
        double Vec3::Module() const{
            return KSqrt(x * x + y * y + z * z);
        }

        double Vec3::ModuleSquare() const{
            return x * x + y * y + z * z;
        }

        Vec3& Vec3::NormalLize(){
            double module = this->Module();
            this->x /= module;
            this->y /= module;
            this->z /= module;
            return *this;
        }

        bool Vec3::NearZero()
        {
            const Float zero = Eps;
            return (fabs(x) < zero) && (fabs(y) < zero) && (fabs(z) < zero);
        }

        Vec3& Vec3::operator+=(const Vec3& right)
        {
            this->x += right.x;
            this->y += right.y;
            this->z += right.z;
            return *this;
        }

        Vec3& Vec3::operator-=(const Vec3& right)
        {
            this->x -= right.x;
            this->y -= right.y;
            this->z -= right.z;
            return *this;
        }

        Vec3& Vec3::operator*=(const double right)
        {
            this->x *= right;
            this->y *= right;
            this->z *= right;
            return *this;
        }

        Vec3& Vec3::operator/=(const double right)
        {
            this->x /= right;
            this->y /= right;
            this->z /= right;
            return *this;
        }

        double& Vec3::operator[](const size_t index)
        {
            //need assert 0 - 2
            return *reinterpret_cast<double*>(reinterpret_cast<uint8_t*>(this) + index * FloatSize);
        }

        double Vec3::operator[](const size_t index) const
        {
            return const_cast<Vec3*>(this)->operator[](index);
        }

        Vec3 SampleUnitSphere()
        {
            Vec3 ret;
            auto theta = acos(1 - 2.0 * KRandom());
            auto phi = KRandom() * Pi * 2.0;

            ret.x = sin(theta) * cos(phi);
            ret.y = sin(theta) * sin(phi);
            ret.z = cos(theta);

            return ret;

            /*while (1) {
                Vec3 ret(KRandom(-1.0, 1.0), KRandom(-1.0, 1.0), KRandom(-1.0, 1.0));
                if (ret.Module() >= 1.0) {
                    continue;
                }
                return ret.NormalLize();
            }*/
        }

        Vec3 SampleHemisphere()
        {
            Vec3 ret;
            auto theta = KRandom() * Pi;
            auto phi = (KRandom() * Pi * 2) - Pi;

            ret.x = sin(theta) * cos(phi);
            ret.y = sin(theta) * sin(phi);
            ret.z = cos(theta);

            return ret;
        }

        Vec3 SampleUniformHemisphere()
        {
            return Vec3();
        }


        Vec3 SampleCircular() {
            auto theta = 2.0 * Pi * KRandom();
            auto r = KSqrt(KRandom());
            return Vec3(r * cos(theta), r * sin(theta), 0.0);
        }
    } // namespace math
} // namespace mortal
