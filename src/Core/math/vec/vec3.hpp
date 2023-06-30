#pragma once
#include "base/calculate.hpp"
namespace mortal
{
    inline namespace math
    { 
        constexpr size_t FloatSize = sizeof(double);

        class Vec3{
        public:
            Vec3() = default;
            Vec3(double _x, double _y, double _z);
            Vec3(const Vec3&) = default;

            double Module() const;
            double ModuleSquare() const;
            Vec3& NormalLize();
            bool NearZero();

            Vec3& operator+=(const Vec3& right);
            Vec3& operator-=(const Vec3& right);
            Vec3& operator*=(const double right);
            Vec3& operator/=(const double right);
            double& operator[](const size_t index);
            double operator[](const size_t index) const;
            bool operator==(const Vec3& rhs) const;
        public:
            double x{ 0.0 };
            double y{ 0.0 };
            double z{ 0.0 };
        };


        static Vec3 operator-(const Vec3& left)
        {
            Vec3 temp;
            temp.x = -left.x;
            temp.y = -left.y;
            temp.z = -left.z;
            return temp;
        }

        static Vec3 operator+(const Vec3& left, const Vec3& right)
        {
            Vec3 temp;
            temp.x = left.x + right.x;
            temp.y = left.y + right.y;
            temp.z = left.z + right.z;
            return temp;
        }

        static Vec3 operator-(const Vec3& left, const Vec3& right)
        {
            Vec3 temp;
            temp.x = left.x - right.x;
            temp.y = left.y - right.y;
            temp.z = left.z - right.z;
            return temp;
        }

        static Vec3 operator*(const Vec3& left, const double right)
        {
            Vec3 temp;
            temp.x = left.x * right;
            temp.y = left.y * right;
            temp.z = left.z * right;
            return temp;
        }

        static Vec3 operator*(const double left, const Vec3& right)
        {
            Vec3 temp;
            temp.x = left * right.x;
            temp.y = left * right.y;
            temp.z = left * right.z;
            return temp;
        }

        static Vec3 operator*(const Vec3& left, const Vec3& right)
        {
            Vec3 temp;
            temp.x = left.x * right.x;
            temp.y = left.y * right.y;
            temp.z = left.z * right.z;
            return temp;
        }

        static Vec3 operator/(const Vec3& left, const double right)
        {
            Vec3 temp;
            temp.x = left.x / right;
            temp.y = left.y / right;
            temp.z = left.z / right;
            return temp;
        }

        static double Dot(const Vec3& left, const Vec3& right)
        {
            double temp = 0.0;
            temp = left.x * right.x + left.y * right.y + left.z * right.z;
            return temp;
        }

        static Vec3 Cross(const Vec3& left, const Vec3& right)
        {
            Vec3 temp;
            temp.x = left.y * right.z - left.z * right.y;
            temp.y = left.z * right.x - left.x * right.z;
            temp.z = left.x * right.y - left.y * right.x;
            return temp;
        }

        static Vec3 Normal(const Vec3& vec)
        {
            double module = vec.Module();
            return Vec3(vec.x / module, vec.y / module, vec.z / module);
        }

        static Vec3 Reflect(const Vec3& vec, const Vec3& normal) {
            return vec - 2.0 * Dot(vec, normal) * normal;
        }
        
        static Vec3 Refract(const Vec3& vec, const Vec3& normal, double eta_etap) {
            auto cosTheta = fmin(Dot(-vec, normal), 1.0);
            auto bvec = eta_etap * (vec + cosTheta * normal);
            auto avec = KSqrt(fabs(1.0 - bvec.ModuleSquare())) * -normal;
            return avec + bvec;
        }

        Vec3 SampleUnitSphere();
        Vec3 SampleHemisphere();
        Vec3 SampleUniformHemisphere();
        Vec3 SampleCircular();
    } // namespace math
    using Point3 = math::Vec3;
    using Color = math::Vec3;
} // namespace mortal

