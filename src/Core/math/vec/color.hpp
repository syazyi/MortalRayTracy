#pragma once
#include <iostream>
#include "vec3.hpp"
#include "base/calculate.hpp"
namespace mortal
{
    inline namespace math
    {
        constexpr float GammaValue = 0.4545454545454545f;

        void WriteColor(std::ostream& os, const Color& col);

        static Color Lerp(const Color& from, const Color& to, float weight) {
            return (1.0f - weight) * from + weight * to;
        }

        //standard gammamapping
        static Color Gamma22(const Color& color) {
            Color ret(powf(color.x, GammaValue), powf(color.y, GammaValue), powf(color.z, GammaValue));
            return ret;
        }

        //quickly gammamapping
        static Color Gamma20(const Color& color) {
            Color ret(KSqrt(color.x), KSqrt(color.y), KSqrt(color.z));
            return ret;
        }

        float Clamp(float value, float min, float max);

    } // namespace math
} // namespace mortal
