#pragma once
#include "geometry/ray.hpp"
#include "hitlist.hpp"
#include "geometry/IHittbale.hpp"
#include <array>
namespace mortal
{

    //class Camera {
    //public:
    //    Point3 position;
    //    float fov;
    //    float aspect;
    //    float near;
    //    float far;
    //};

    class Scene{
    public:
        static Color BackgroundColor(const Ray& ray);
        void Play();
        Color RayCastColor(const Ray& ray, uint8_t depth);
    private:
        void WriteInPPMTest(const int width, const int height);
        void WriteInPPMSingleColor(const int width, const int height, const Color& color);

        //only Test
        void RandomWorld();
    public:
        static const int width = 400;
        static const int height = 225;
        static const int antialiasingSamplerCount = 100;
        inline static std::array<std::array<Color, width>, height> framebuffer;
    private:
        HitList world;
        MaterialManagement materials;
    };
} // namespace mortal
