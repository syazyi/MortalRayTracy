#include "scene.hpp"
#include <iostream>
#include <fstream>

#include "scene.hpp"
#include "vec/color.hpp"
#include "camera.hpp"
#include "geometry/sphere.hpp"
#include "base/calculate.hpp"
#include "material/material.hpp"
#include "material/lambertian.hpp"
#include "material/metal.hpp"
#include "material/dielectric.hpp"
#include "geometry/move_sphere.hpp"
#include "material/lambertian_texture.hpp"
#include "texture/check_texture.hpp"
#include "texture/image_texture.hpp"
#include "material/diffuse_light.hpp"
namespace mortal
{
    Color Scene::BackgroundColor(const Ray& ray){
        //auto t = 0.5f * (ray.direction.y + 1.0f);
        //return math::Lerp(Color(1.0f, 1.0f, 1.0f),  Color(0.5f, 0.7f, 1.0f), t);
        return Color(0.0f, 0.0f, 0.0f);
    }

    void Scene::Play(){
        //mortal::Color gray(0.5f, 0.5f, 0.5f);
	    //WriteInPPMSingleColor(width, height, gray);
	    WriteInPPMTest(width, height);
    }

    Color Scene::RayCastColor(const Ray& ray, uint8_t depth)
    {
        /*if (sphere.IsIntersectionRay(ray)) {
            return Color(1.0f, 0.0f, 0.0f);
        }*/

        if (depth == 0) {
            return Color(0.0f, 0.0f, 0.0f);
        }

        HitResult hitResult;
        if (world.HitIntersectionRay(ray, 0.01f, Infinity, hitResult)) {
            /*
                print normal
                auto normal = hitResult.normal;
                return 0.5 * Color(normal.x + 1.f, normal.y + 1.f, normal.z + 1.f);
            */

            //Todo:Through hitresult information to get an new ray
            //auto reflectRay = GetReflectDir(hitResult);
            Ray reflectRay;
            Color attenuation;
            Color emitted = hitResult.material->Emitted(hitResult.u, hitResult.v, hitResult.position);
            if (hitResult.material->Scatter(ray, hitResult, attenuation, reflectRay)) {
                return attenuation * RayCastColor(reflectRay, depth - 1) + emitted;
            }
            return emitted;
        }
        return BackgroundColor(ray);
    }

//private
    void Scene::WriteInPPMTest(const int width, const int height){
        //Material
        materials.Add("Ground", std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f)));
        materials.Add("Center", std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f)));
        materials.Add("Left_Metal", std::make_shared<Metal>(Color(0.8f, 0.8f, 0.8f), 0.3f));
        materials.Add("Right_Metal", std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f)));
        materials.Add("Dielectric", std::make_shared<Dielectric>(1.5f));

        //world
        //world.Add(std::make_shared<Sphere>(Point3(0.0f, -100.5, -1.0f), 100.0f, materials.Get("Ground")));
        //world.Add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, materials.Get("Center")));
        //world.Add(std::make_shared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), 0.5f, materials.Get("Dielectric")));
        //world.Add(std::make_shared<Sphere>(Point3(-1.0f, 0.0f, -1.0f), -0.4f, materials.Get("Dielectric")));
        //world.Add(std::make_shared<Sphere>(Point3(1.0f, 0.0f, -1.0f), 0.5f, materials.Get("Right_Metal")));
        RandomWorld(WorldType::ELightTestWorld);

        //Camera
        float aspect_ration = static_cast<float>(width) / static_cast<float>(height);
        Point3 lookFrom = Point3(13.0f, 2.0f, 3.0f);
        Point3 lookAt = Point3(0.0f, 0.0f, 0.0f);
        Camera camera(lookFrom, lookAt, Vec3f(0.0f, 1.0f, 0.0f), 20.0f, aspect_ration, 0.1f, 10.f, 0.0f, 0.1f);

        float bar = 1;
        std::ofstream myfile;
        myfile.open("test.ppm");
        myfile << "P3\n" << width << " " << height << "\n255\n";
//#pragma omp parallel for
#pragma omp parallel for schedule(dynamic, 1)
        for (int i = height - 1; i >= 0; i--) {
            std::cout << "\rprogress: " << (int)(bar / height * 100) << "% " << std::flush;
            bar++;
            for (int j = 0; j < width; j++) {
                Color color;
                for (int spp = 0; spp < antialiasingSamplerCount; spp++) {
                    auto u = float(j + KRandom()) / (width - 1);
                    auto v = float(i + KRandom()) / (height - 1);
                    Ray ray = camera.GetRay(u, v);
                    color += RayCastColor(ray, 50);
                }
                color /= antialiasingSamplerCount;
                framebuffer[height - 1 - i][j] = color;
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                mortal::math::WriteColor(myfile, framebuffer[i][j]);
            }
        }
        myfile.close();
        std::cout << "\nDone.\n";
    }

    void Scene::WriteInPPMSingleColor(const int width, const int height, const Color& color){
        float bar = 1;
        std::ofstream myfile;
        myfile.open("test.ppm");
        myfile << "P3\n" << width << " " << height << "\n255\n";
        for (int i = 0; i < height; i++) {
            std::cout << "\rprogress: " << (int)(bar / height * 100) << "% " << std::flush;
            bar++;
            for (int j = 0; j < width; j++) {
                mortal::math::WriteColor(myfile, color);
            }
        }
        myfile.close();
        std::cout << "\nDone.\n";
    }

    void mortal::Scene::RandomWorld(WorldType type)
    {
        switch (type)
        {
        case WorldType::ERandomWorld :
            {
                materials.Add("ground_material", std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f)));
                materials.Add("ground_material_check", std::make_shared<LambertianWithTexture>(std::make_shared<CheckTexture>()));
                materials.Add("sphere_material_glass", std::make_shared<Dielectric>(1.5f));

                //world.Add(std::make_shared<Sphere>(Point3(0.0f, -1000.f, 0.0f), 1000.f, materials.Get("ground_material")));
                world.Add(std::make_shared<Sphere>(Point3(0.0f, -1000.f, 0.0f), 1000.f, materials.Get("ground_material_check")));

                for (int a = -11; a < 11; a++) {
                    for (int b = -11; b < 11; b++) {
                        auto choose_mat = KRandom();
                        Point3 center(a + 0.9f * KRandom(), 0.2f, b + 0.9f * KRandom());

                        if ((center - Point3(4.0f, 0.2f, 0.f)).Module() > 0.9f) {
                            if (choose_mat < 0.8f) {
                                // diffuse
                                auto albedo = Color(KRandom(), KRandom(), KRandom()) * Color(KRandom(), KRandom(), KRandom());
                                auto center2 = center + Point3(0, KRandom(0.5f, 1.5f), 0);
                                world.Add(std::make_shared<MoveSphere>(center, center2, 0.0f, 1.0f, 0.2f, std::make_shared<Lambertian>(albedo)));
                                //world.Add(std::make_shared<Sphere>(center, 0.2f, std::make_shared<Lambertian>(albedo)));
                            }
                            else if (choose_mat < 0.95f) {
                                // metal
                                auto albedo = Color(KRandom(0.5f, 1.0f), KRandom(0.5f, 1.0f), KRandom(0.5f, 1.0f));
                                auto fuzz = KRandom(0.5f, 1.0f);
                                auto sphere_material = std::make_shared<Metal>(albedo, fuzz);
                                world.Add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                            }
                            else {
                                // glass
                                world.Add(std::make_shared<Sphere>(center, 0.2f, materials.Get("sphere_material_glass")));
                            }
                        }
                    }
                }

                materials.Add("material_dielectric", std::make_shared<Dielectric>(1.5f));
                world.Add(std::make_shared<Sphere>(Point3(0.f, 1.f, 0.f), 1.0f, materials.Get("material_dielectric")));

                materials.Add("material_lambertian", std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f)));
                world.Add(std::make_shared<Sphere>(Point3(-4.0f, 1.0f, 0.0f), 1.0f, materials.Get("material_lambertian")));

                materials.Add("material_metal", std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f));
                world.Add(std::make_shared<Sphere>(Point3(4.0f, 1.0f, 0.0f), 1.0f, materials.Get("material_metal")));

            }
            break;
        case WorldType::ETextureTestWorld:
            {
                materials.Add("TextureTestMaterial", std::make_shared<LambertianWithTexture>(std::make_shared<ImageTexture>("back.jpg")));
                auto globe = std::make_shared<Sphere>(Point3(0.0f, 0.0f, 0.0f), 2.0f, materials.Get("TextureTestMaterial"));
                world.Add(globe);
            }
            break;
        case WorldType::ELightTestWorld:
            {
                materials.Add("ground_material_check", std::make_shared<LambertianWithTexture>(std::make_shared<CheckTexture>()));  
                materials.Add("TextureTestMaterial", std::make_shared<LambertianWithTexture>(std::make_shared<ImageTexture>("back.jpg")));
                materials.Add("TestLight", std::make_shared<DiffuseLight>(Color(1.0f, 1.0f, 1.0f)));

                world.Add(std::make_shared<Sphere>(Point3(0.0f, -1000.f, 0.0f), 1000.f, materials.Get("ground_material_check")));
                world.Add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, 0.0f), 2.0f, materials.Get("TextureTestMaterial")));
                world.Add(std::make_shared<Sphere>(Point3(2.0f, 0.0f, -3.0f), 1.0f, materials.Get("TestLight")));
            }
            break;
        case WorldType::ECornellBox: 
            {
                
            }
            break;
        }
    }
} // namespace mortal
