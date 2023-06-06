#include "vec3.hpp"
#include "base/calculate.hpp"
namespace mortal
{
    inline namespace math
    {

        Vec3f::Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
        
        float Vec3f::Module() const{
            return KSqrt(x * x + y * y + z * z);
        }

        float Vec3f::ModuleSquare() const{
            return x * x + y * y + z * z;
        }

        Vec3f& Vec3f::NormalLize(){
            float module = this->Module();
            this->x /= module;
            this->y /= module;
            this->z /= module;
            return *this;
        }

        bool Vec3f::NearZero()
        {
            const Float zero = Eps;
            return (fabs(x) < zero) && (fabs(y) < zero) && (fabs(z) < zero);
        }

        Vec3f& Vec3f::operator+=(const Vec3f& right)
        {
            this->x += right.x;
            this->y += right.y;
            this->z += right.z;
            return *this;
        }

        Vec3f& Vec3f::operator-=(const Vec3f& right)
        {
            this->x -= right.x;
            this->y -= right.y;
            this->z -= right.z;
            return *this;
        }

        Vec3f& Vec3f::operator*=(const float right)
        {
            this->x *= right;
            this->y *= right;
            this->z *= right;
            return *this;
        }

        Vec3f& Vec3f::operator/=(const float right)
        {
            this->x /= right;
            this->y /= right;
            this->z /= right;
            return *this;
        }

        float& Vec3f::operator[](const size_t index)
        {
            //need assert 0 - 2
            return *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(this) + index * FloatSize);
        }

        float Vec3f::operator[](const size_t index) const
        {
            return const_cast<Vec3f*>(this)->operator[](index);
        }

        Vec3f SampleUnitSphere()
        {
            Vec3f ret;
            auto theta = (KRandom() * Pi * 2) - Pi;
            auto phi = (KRandom() * Pi * 2) - Pi;

            ret.x = sin(theta) * cos(phi);
            ret.y = sin(theta) * sin(phi);
            ret.z = cos(theta);

            return ret;
        }

        Vec3f SampleHemisphere()
        {
            Vec3f ret;
            auto theta = KRandom() * Pi;
            auto phi = (KRandom() * Pi * 2) - Pi;

            ret.x = sin(theta) * cos(phi);
            ret.y = sin(theta) * sin(phi);
            ret.z = cos(theta);

            return ret;
        }

        Vec3f SampleUniformHemisphere()
        {
            return Vec3f();
        }


        Vec3f SampleCircular() {
            auto theta = 2.0f * Pi * KRandom();
            auto r = KSqrt(KRandom());
            return Vec3f(r * cos(theta), r * sin(theta), 0.0f);
        }
    } // namespace math
} // namespace mortal
