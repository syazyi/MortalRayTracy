#pragma once
#include "pdf.hpp"
#include "base/onb.hpp"
namespace mortal
{
    class CosinePDF : public PDF {
    public:
        CosinePDF() = default;
        explicit CosinePDF(const Vec3& normal);

        virtual double Value(const Vec3& dir) const override;
        virtual Vec3 Generate() const override;
    private:
        ONB m_uvw;
    };


} // namespace moetal
