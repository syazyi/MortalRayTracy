#pragma once
#include "geometry/ray.hpp"
#include "hitlist.hpp"
#include "geometry/IHittbale.hpp"
#include <array>
namespace mortal
{
    class Camera;

    enum class WorldType{
        ERandomWorld,
        ETextureTestWorld,
        ELightTestWorld,
        ECornellBox
    };

    class Scene{
    public:
        static Color BackgroundColor(const Ray& ray);
        void Play();
        Color RayCastColor(const Ray& ray, std::shared_ptr<IHittbale> light, uint8_t depth);
    private:
        void WriteInPPMTest(const int width, const int height);
        void WriteInPPMSingleColor(const int width, const int height, const Color& color);

        //only Test
        std::shared_ptr<IHittbale> RandomWorld(WorldType type, Camera& camera);
    public:
        static const int width = 600;
        static const int height = 600;
        static const int antialiasingSamplerCount = 1000;
        inline static std::array<std::array<Color, width>, height> framebuffer;
    private:
        HitList world;
        MaterialManagement materials;
    };
} // namespace mortal
