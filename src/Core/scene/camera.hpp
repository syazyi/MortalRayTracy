#pragma once
#include "geometry/ray.hpp"
namespace mortal
{
    class Camera {
    public:
        explicit Camera(Point3 lookFrom, Point3 lookAt, Vec3f up, float fov, float aspect_ration, float apeture, float focusDist);
        Ray GetRay(float s, float t) const;
    private:
        Point3 m_Position;
        Vec3f m_Horizontal;
        Vec3f m_Vertical;
        Vec3f m_LowerLeftCorner;
        Vec3f m_ViewMatU;
        Vec3f m_ViewMatV;
        Vec3f m_ViewMatW;
        float m_LenRadius;
    };
} // namespace mortal
