#include "mixture_pdf.hpp"

namespace mortal
{
    

    
    MixturePDF::MixturePDF(std::shared_ptr<PDF> p1, std::shared_ptr<PDF> p2) : m_Src(p1), m_Dst(p2)
    {
    }

    double MixturePDF::Value(const Vec3& dir) const
    {
        return 0.5 * m_Src->Value(dir) + 0.5 * m_Dst->Value(dir) ;
    }

    Vec3 MixturePDF::Generate() const
    {
        if (KRandom() < 0.5) {
            return m_Src->Generate();
        }
        return m_Dst->Generate();
    }

} // namespace moetal
