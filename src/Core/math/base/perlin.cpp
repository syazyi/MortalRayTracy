#include "perlin.hpp"

namespace mortal
{
    

    
    Perlin::Perlin()
    {
        m_RandFloatValues.resize(PerlinPointCount);
        for (int i = 0; i < PerlinPointCount; i++) {
            m_RandFloatValues[i] = KRandom();
        }
    }

    Perlin::~Perlin()
    {

    }

} // namespace mortal
