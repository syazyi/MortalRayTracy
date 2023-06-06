#include "camera.hpp"
namespace mortal
{
    Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3f up, float fov, float aspect_ration, float apeture, float focusDist, float time0, float time1)
    {
        m_Position = lookFrom;
        auto h = tan(Radians(fov) / 2.0f);
        auto viewPortHeight = 2.0f * h;
        auto viewPortWidth = viewPortHeight * aspect_ration;

        m_ViewMatW = (lookFrom - lookAt).NormalLize();
        m_ViewMatU = Cross(up, m_ViewMatW).NormalLize();
        m_ViewMatV = Cross(m_ViewMatW, m_ViewMatU).NormalLize();

        m_Horizontal = focusDist * viewPortWidth * m_ViewMatU;
        m_Vertical = focusDist * viewPortHeight * m_ViewMatV;
        m_LowerLeftCorner = -m_Horizontal / 2.0f - m_Vertical / 2.0f - focusDist * m_ViewMatW;
        m_LenRadius = apeture / 2.0f;

        m_Time0 = time0;
        m_Time1 = time1;
    }

    Ray Camera::GetRay(float s, float t) const
    {
        Vec3f rd = m_LenRadius * SampleCircular();
        Vec3f offset = m_ViewMatU * rd.x + m_ViewMatV * rd.y;
        return Ray(m_Position + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - offset, KRandom(m_Time0, m_Time1));
    }
} // namespace mortal
