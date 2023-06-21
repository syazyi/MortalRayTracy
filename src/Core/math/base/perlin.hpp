#pragma once 
#include "base/calculate.hpp"
#include <vector>
namespace mortal
{
    class Perlin final{
    public:
        Perlin();
        ~Perlin();


    private:
        constexpr static int PerlinPointCount = 256;
        std::vector<float> m_RandFloatValues;

    };

    
} // namespace mortal
