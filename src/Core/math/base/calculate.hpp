#pragma once
#include <limits>
#include <random>
namespace mortal
{
    inline namespace math
    {
        using Float = double;
        constexpr Float Infinity = std::numeric_limits<Float>::infinity();
        constexpr Float Pi = 3.1415926535897932385;
        constexpr Float OneDivPi = 1.0f / Pi;
        constexpr Float OneDiv2Pi = 1.0f / (2.0 * Pi);
        constexpr Float OdPi = 1 / 180.0;
        constexpr Float Eps = 1e-5;
        Float Radians(Float degrees);

        double KSqrt(double x);
        double InvSqrt(double x);
        Float KRandom();
        Float KRandom(Float min, Float max);
    } // namespace math
    
} // namespace mortal
