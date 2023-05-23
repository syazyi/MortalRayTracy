#pragma once
#include "base/calculate.hpp"
namespace mortal
{
    inline namespace math
    { 
        class Vec3f{
        public:
            Vec3f() = default;
            Vec3f(float _x, float _y, float _z);
            Vec3f(const Vec3f&) = default;

            float Module() const;
            float ModuleSquare() const;
            Vec3f& NormalLize();
            bool NearZero();

            Vec3f& operator+=(const Vec3f& right);
            Vec3f& operator-=(const Vec3f& right);
            Vec3f& operator*=(const float right);
            Vec3f& operator/=(const float right);
        public:
            float x{ 0.0f };
            float y{ 0.0f };
            float z{ 0.0f };
        };


        static Vec3f operator-(const Vec3f& left)
        {
            Vec3f temp;
            temp.x = -left.x;
            temp.y = -left.y;
            temp.z = -left.z;
            return temp;
        }

        static Vec3f operator+(const Vec3f& left, const Vec3f& right)
        {
            Vec3f temp;
            temp.x = left.x + right.x;
            temp.y = left.y + right.y;
            temp.z = left.z + right.z;
            return temp;
        }

        static Vec3f operator-(const Vec3f& left, const Vec3f& right)
        {
            Vec3f temp;
            temp.x = left.x - right.x;
            temp.y = left.y - right.y;
            temp.z = left.z - right.z;
            return temp;
        }

        static Vec3f operator*(const Vec3f& left, const float right)
        {
            Vec3f temp;
            temp.x = left.x * right;
            temp.y = left.y * right;
            temp.z = left.z * right;
            return temp;
        }

        static Vec3f operator*(const float left, const Vec3f& right)
        {
            Vec3f temp;
            temp.x = left * right.x;
            temp.y = left * right.y;
            temp.z = left * right.z;
            return temp;
        }

        static Vec3f operator*(const Vec3f& left, const Vec3f& right)
        {
            Vec3f temp;
            temp.x = left.x * right.x;
            temp.y = left.y * right.y;
            temp.z = left.z * right.z;
            return temp;
        }

        static Vec3f operator/(const Vec3f& left, const float right)
        {
            Vec3f temp;
            temp.x = left.x / right;
            temp.y = left.y / right;
            temp.z = left.z / right;
            return temp;
        }

        static float Dot(const Vec3f& left, const Vec3f& right)
        {
            float temp = 0.0f;
            temp = left.x * right.x + left.y * right.y + left.z * right.z;
            return temp;
        }

        static Vec3f Cross(const Vec3f& left, const Vec3f& right)
        {
            Vec3f temp;
            temp.x = left.y * right.z - left.z * right.y;
            temp.y = left.z * right.x - left.x * right.z;
            temp.z = left.x * right.y - left.y * right.x;
            return temp;
        }

        static Vec3f Normal(const Vec3f& vec)
        {
            float module = vec.Module();
            return Vec3f(vec.x / module, vec.y / module, vec.z / module);
        }

        static Vec3f Reflect(const Vec3f& vec, const Vec3f& normal) {
            return vec - 2.0f * Dot(vec, normal) * normal;
        }
        
        static Vec3f Refract(const Vec3f& vec, const Vec3f& normal, float eta_etap) {
            auto cosTheta = fmin(Dot(-vec, normal), 1.0f);
            auto bvec = eta_etap * (vec + cosTheta * normal);
            auto avec = KSqrt(fabs(1.0f - bvec.ModuleSquare())) * -normal;
            return avec + bvec;
        }

        Vec3f SampleUnitSphere();
        Vec3f SampleHemisphere();
        Vec3f SampleUniformHemisphere();
        Vec3f SampleCircular();
    } // namespace math
    using Point3 = math::Vec3f;
    using Color = math::Vec3f;
} // namespace mortal

