#pragma once
#include "vec/vec3.hpp"
namespace mortal
{
    class PDF{
    public:
        virtual ~PDF();

        virtual double Value(const Vec3& dir) const = 0;
        virtual Vec3 Generate() const = 0;   
    };



} // namespace mortal
