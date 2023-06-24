#pragma once
#include "geometry/ray.hpp"
namespace mortal
{
    class Camera {
    public:
        Camera() = default;
        explicit Camera(Point3 lookFrom, Point3 lookAt, Vec3 up, double fov, double aspect_ration, double apeture, double focusDist, double time0, double time1);
        Ray GetRay(double s, double t) const;
    private:
        Point3 m_Position;
        Vec3 m_Horizontal;
        Vec3 m_Vertical;
        Vec3 m_LowerLeftCorner;
        Vec3 m_ViewMatU;
        Vec3 m_ViewMatV;
        Vec3 m_ViewMatW;
        double m_LenRadius;
        double m_Time0;
        double m_Time1;
    };
} // namespace mortal
