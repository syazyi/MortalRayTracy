#pragma once
#include "pdf/pdf.hpp"
namespace mortal
{
    class MixturePDF : public PDF{
    public:
        MixturePDF() = default;
        MixturePDF(std::shared_ptr<PDF> p1, std::shared_ptr<PDF> p2);

        virtual double Value(const Vec3& dir) const override;
        virtual Vec3 Generate() const override;
    private:
        std::shared_ptr<PDF> m_Src;
        std::shared_ptr<PDF> m_Dst;
    };


} // namespace mortal
