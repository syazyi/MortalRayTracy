#include "camera.hpp"
namespace mortal
{
    Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 up, double fov, double aspect_ration, double apeture, double focusDist, double time0, double time1)
    {
        m_Position = lookFrom;
        auto h = tan(Radians(fov) / 2.0);
        auto viewPortHeight = 2.0 * h;
        auto viewPortWidth = viewPortHeight * aspect_ration;

        m_ViewMatW = (lookFrom - lookAt).NormalLize();
        m_ViewMatU = Cross(up, m_ViewMatW).NormalLize();
        m_ViewMatV = Cross(m_ViewMatW, m_ViewMatU).NormalLize();

        m_Horizontal = focusDist * viewPortWidth * m_ViewMatU;
        m_Vertical = focusDist * viewPortHeight * m_ViewMatV;
        m_LowerLeftCorner = -m_Horizontal / 2.0 - m_Vertical / 2.0 - focusDist * m_ViewMatW;
        m_LenRadius = apeture / 2.0;

        m_Time0 = time0;
        m_Time1 = time1;
    }

    Ray Camera::GetRay(double s, double t) const
    {
        Vec3 rd = m_LenRadius * SampleCircular();
        Vec3 offset = m_ViewMatU * rd.x + m_ViewMatV * rd.y;
        return Ray(m_Position + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - offset, KRandom(m_Time0, m_Time1));
    }
} // namespace mortal
