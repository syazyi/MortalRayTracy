#include "color.hpp"

namespace mortal
{
    inline namespace math
    {   
        void WriteColor(std::ostream& os, const Color& col){
            auto Color = Gamma20(col);
            //auto Color = col;
            os 
            << static_cast<int>(255.999 * Clamp(Color.x, 0.0, 1.0)) << " "
            << static_cast<int>(255.999 * Clamp(Color.y, 0.0, 1.0)) << " "
            << static_cast<int>(255.999 * Clamp(Color.z, 0.0, 1.0)) << "\n";
        }

        double Clamp(double value, double min, double max)
        {
            if (value < min) {
                return min;
            }
            if (value > max) {
                return max;
            }
            return value;
        }
    } // namespace math
    
} // namespace mortal
