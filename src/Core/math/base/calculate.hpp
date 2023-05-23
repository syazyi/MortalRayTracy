#pragma once
#include <limits>
#include <random>
namespace mortal
{
    inline namespace math
    {
        using Float = float;
        constexpr Float Infinity = std::numeric_limits<Float>::infinity();
        constexpr Float Pi = 3.1415926535897932385;
        constexpr Float OdPi = 1 / 180.0;
        constexpr Float Eps = 1e-5;
        Float Radians(Float degrees);

        float KSqrt(float x);
        float InvSqrt(float x);
        Float KRandom();
        Float KRandom(Float min, Float max);
    } // namespace math
    
} // namespace mortal
