#include "ONB.hpp"

namespace mortal
{
    

    
    void ONB::BuildFromW(const Vec3& n)
    {
        w = Normal(n);
        Vec3 a = (fabs(w.x) > 0.9) ? Vec3(0, 1, 0) : Vec3(1, 0, 0);
        v = Cross(w, a).NormalLize();
        u = Cross(w, v);
    }

} // namespace mortal
