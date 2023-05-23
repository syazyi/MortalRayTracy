#include "calculate.hpp"

namespace mortal
{
    inline namespace math
    {
        Float Radians(Float degrees)
        {
            return degrees * Pi * OdPi;
        }
        float KSqrt(float x){
//not be use
#ifdef DEBUGNOT
            float a = x;
            auto p = (unsigned int*)&x;
            *p = (*p + 0x3f76cf62) >> 1;
            x = (x + a / x) / 2;
            return x;
#else
            return sqrtf(x);
#endif // DEBUG

        }

        float InvSqrt(float x)
        {
            float xhalf = 0.5f * x;
            int i = *(int*)&x;
            i = 0x5f3759df - (i >> 1);
            x = *(float*)&i;
            x = x * (1.5f - xhalf * x * x);
            return x;
        }

        Float KRandom()
        {
            static std::uniform_real_distribution<Float> distribution(0.0, 1.0);
            static std::mt19937 generator;
            return distribution(generator);
        }

        Float KRandom(Float min, Float max)
        {
            return min + (max - min) * KRandom();
        }


    } // namespace math
} // namespace mortal
