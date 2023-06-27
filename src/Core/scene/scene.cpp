#include "scene.hpp"
#include <iostream>
#include <fstream>

#include "scene.hpp"
#include "camera.hpp"
#include "vec/color.hpp"
#include "base/calculate.hpp"
#include "geometry/sphere.hpp"
#include "geometry/plane.hpp"
#include "geometry/move_sphere.hpp"
#include "geometry/box.hpp"
#include "geometry/constant_medium.hpp"
#include "material/material.hpp"
#include "material/lambertian.hpp"
#include "material/metal.hpp"
#include "material/dielectric.hpp"
#include "material/lambertian_texture.hpp"
#include "material/diffuse_light.hpp"
#include "material/isotropic.hpp"
#include "texture/check_texture.hpp"
#include "texture/image_texture.hpp"
namespace mortal
{
    Color Scene::BackgroundColor(const Ray& ray){
        //auto t = 0.5f * (ray.direction.y + 1.0);
        //return math::Lerp(Color(1.0, 1.0, 1.0),  Color(0.5f, 0.7f, 1.0), t);
        return Color(0.0, 0.0, 0.0);
    }

    void Scene::Play(){
        //mortal::Color gray(0.5f, 0.5f, 0.5f);
	    //WriteInPPMSingleColor(width, height, gray);
	    WriteInPPMTest(width, height);
    }

    Color Scene::RayCastColor(const Ray& ray, uint8_t depth)
    {
        /*if (sphere.IsIntersectionRay(ray)) {
            return Color(1.0, 0.0, 0.0);
        }*/

        if (depth == 0) {
            return Color(0.0, 0.0, 0.0);
        }

        HitResult hitResult;
        if (world.HitIntersectionRay(ray, 0.001, Infinity, hitResult)) {
            /*
                print normal
                auto normal = hitResult.normal;
                return 0.5 * Color(normal.x + 1.f, normal.y + 1.f, normal.z + 1.f);
            */

            //Todo:Through hitresult information to get an new ray
            //auto reflectRay = GetReflectDir(hitResult);
            Ray reflectRay;
            Color albedo;
            Color emitted = hitResult.material->Emitted(hitResult.u, hitResult.v, hitResult.position);
            double pdf;
            if (hitResult.material->Scatter(ray, hitResult, albedo, reflectRay, pdf)) {
                return (albedo * hitResult.material->ScatterPDF(ray, hitResult, reflectRay) *  RayCastColor(reflectRay, depth - 1)) / pdf + emitted;
            }
            return emitted;
        }
        return BackgroundColor(ray);
    }

//private
    void Scene::WriteInPPMTest(const int width, const int height){
        //Material
        materials.Add("Ground", std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0)));
        materials.Add("Center", std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f)));
        materials.Add("Left_Metal", std::make_shared<Metal>(Color(0.8f, 0.8f, 0.8f), 0.3f));
        materials.Add("Right_Metal", std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f)));
        materials.Add("Dielectric", std::make_shared<Dielectric>(1.5f));

        //world
        //world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materials.Get("Ground")));
        //world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5f, materials.Get("Center")));
        //world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5f, materials.Get("Dielectric")));
        //world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.4f, materials.Get("Dielectric")));
        //world.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5f, materials.Get("Right_Metal")));
        Camera camera;

        RandomWorld(WorldType::ECornellBox, camera);

        //Camera

        double bar = 1;
        std::ofstream myfile;
        myfile.open("test.ppm");
        myfile << "P3\n" << width << " " << height << "\n255\n";
#pragma omp parallel for
//#pragma omp parallel for schedule(dynamic, 1)
        for (int i = height - 1; i >= 0; i--) {
            std::cout << "\rprogress: " << (int)(bar / height * 100) << "% " << std::flush;
            bar++;
            for (int j = 0; j < width; j++) {
                Color color;
                for (int spp = 0; spp < antialiasingSamplerCount; spp++) {
                    auto u = double(j + KRandom()) / (width - 1);
                    auto v = double(i + KRandom()) / (height - 1);
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
        double bar = 1;
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

    void mortal::Scene::RandomWorld(WorldType type, Camera& camera)
    {
        switch (type)
        {
        case WorldType::ERandomWorld :
            {
                double aspect_ration = static_cast<double>(width) / static_cast<double>(height);
                Point3 lookFrom = Point3(13.0, 2.0, 3.0);
                Point3 lookAt = Point3(0.0, 0.0, 0.0);
                camera = Camera(lookFrom, lookAt, Vec3(0.0f, 1.0f, 0.0f), 20.0f, aspect_ration, 0.1f, 10.f, 0.0f, 0.1f);

                materials.Add("ground_material", std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f)));
                materials.Add("ground_material_check", std::make_shared<LambertianWithTexture>(std::make_shared<CheckTexture>()));
                materials.Add("sphere_material_glass", std::make_shared<Dielectric>(1.5f));

                //world.Add(std::make_shared<Sphere>(Point3(0.0, -1000.f, 0.0), 1000.f, materials.Get("ground_material")));
                world.Add(std::make_shared<Sphere>(Point3(0.0, -1000.f, 0.0), 1000.f, materials.Get("ground_material_check")));

                for (int a = -11; a < 11; a++) {
                    for (int b = -11; b < 11; b++) {
                        auto choose_mat = KRandom();
                        Point3 center(a + 0.9f * KRandom(), 0.2f, b + 0.9f * KRandom());

                        if ((center - Point3(4.0, 0.2f, 0.f)).Module() > 0.9f) {
                            if (choose_mat < 0.8f) {
                                // diffuse
                                auto albedo = Color(KRandom(), KRandom(), KRandom()) * Color(KRandom(), KRandom(), KRandom());
                                auto center2 = center + Point3(0, KRandom(0.5f, 1.5f), 0);
                                world.Add(std::make_shared<MoveSphere>(center, center2, 0.0, 1.0, 0.2f, std::make_shared<Lambertian>(albedo)));
                                //world.Add(std::make_shared<Sphere>(center, 0.2f, std::make_shared<Lambertian>(albedo)));
                            }
                            else if (choose_mat < 0.95f) {
                                // metal
                                auto albedo = Color(KRandom(0.5f, 1.0), KRandom(0.5f, 1.0), KRandom(0.5f, 1.0));
                                auto fuzz = KRandom(0.5f, 1.0);
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
                world.Add(std::make_shared<Sphere>(Point3(0.f, 1.f, 0.f), 1.0, materials.Get("material_dielectric")));

                materials.Add("material_lambertian", std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f)));
                world.Add(std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, materials.Get("material_lambertian")));

                materials.Add("material_metal", std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0));
                world.Add(std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, materials.Get("material_metal")));

            }
            break;
        case WorldType::ETextureTestWorld:
            {
                double aspect_ration = static_cast<double>(width) / static_cast<double>(height);
                Point3 lookFrom = Point3(13.0, 2.0, 3.0);
                Point3 lookAt = Point3(0.0, 0.0, 0.0);
                camera = Camera(lookFrom, lookAt, Vec3(0.0f, 1.0f, 0.0f), 20.0f, aspect_ration, 0.1f, 10.f, 0.0f, 0.1f);

                materials.Add("TextureTestMaterial", std::make_shared<LambertianWithTexture>(std::make_shared<ImageTexture>("back.jpg")));
                auto globe = std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 2.0, materials.Get("TextureTestMaterial"));
                world.Add(globe);
            }
            break;
        case WorldType::ELightTestWorld:
            {
                double aspect_ration = static_cast<double>(width) / static_cast<double>(height);
                Point3 lookFrom = Point3(13.0, 2.0, 3.0);
                Point3 lookAt = Point3(0.0, 0.0, 0.0);
                camera = Camera(lookFrom, lookAt, Vec3(0.0f, 1.0f, 0.0f), 20.0f, aspect_ration, 0.1f, 10.f, 0.0f, 0.1f);

                materials.Add("ground_material_check", std::make_shared<LambertianWithTexture>(std::make_shared<CheckTexture>()));  
                materials.Add("TextureTestMaterial", std::make_shared<LambertianWithTexture>(std::make_shared<ImageTexture>("back.jpg")));
                materials.Add("TestLight", std::make_shared<DiffuseLight>(Color(1.0, 1.0, 1.0)));

                world.Add(std::make_shared<Sphere>(Point3(0.0, -1000.f, 0.0), 1000.f, materials.Get("ground_material_check")));
                world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, 0.0), 2.0, materials.Get("TextureTestMaterial")));
                world.Add(std::make_shared<Sphere>(Point3(0.0, 3.0, 0.0), 1.0, materials.Get("TestLight")));
                world.Add(std::make_shared<Plane>(3.0, 1.0, 5.0, 3.0, -2.0, PlaneCategory::EXY, materials.Get("TestLight")));
            }
            break;
        case WorldType::ECornellBox: 
            {
                double aspect_ration = static_cast<double>(width) / static_cast<double>(height);
                Point3 lookFrom = Point3(278.0, 278.0, -800.0);
                Point3 lookAt = Point3(278.0, 278.0, 0.0);
                camera = Camera(lookFrom, lookAt, Vec3(0.0, 1.0, 0.0), 40.0, aspect_ration, 0.0, 10000.0, 0.0, 1.0);

                materials.Add("RedDiffuse", std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05)));
                materials.Add("WhiteDiffuse", std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73)));
                materials.Add("GreenDiffuse", std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15)));
                materials.Add("Light", std::make_shared<DiffuseLight>(Color(15.0, 15.0, 15.0)));
                materials.Add("IsotropicWhite", std::make_shared<Isotropic>(Color(1.0, 1.0, 1.0)));
                materials.Add("IsotropicBlack", std::make_shared<Isotropic>(Color(0.0, 0.0, 0.0)));

                world.Add(std::make_shared<Plane>(0.0, 0.0, 555.0, 555.0, 555.0, PlaneCategory::EYZ, materials.Get("GreenDiffuse")));
                world.Add(std::make_shared<Plane>(0.0, 0.0, 555.0, 555.0, 0.0, PlaneCategory::EYZ, materials.Get("RedDiffuse")));
                world.Add(std::make_shared<Plane>(213, 227, 343, 332, 554.999, PlaneCategory::EXZ, materials.Get("Light")));
                //world.Add(std::make_shared<Plane>(113.0, 127.0, 443.0, 432.0, 554.999, PlaneCategory::EXZ, materials.Get("Light")));
                world.Add(std::make_shared<Plane>(0.0, 0.0, 555.0, 555.0, 0.0, PlaneCategory::EXZ, materials.Get("WhiteDiffuse")));
                world.Add(std::make_shared<Plane>(0.0, 0.0, 555.0, 555.0, 555.0, PlaneCategory::EXZ, materials.Get("WhiteDiffuse")));
                world.Add(std::make_shared<Plane>(0.0, 0.0, 555.0, 555.0, 555.0, PlaneCategory::EXY, materials.Get("WhiteDiffuse")));

                //auto box1 = std::make_shared<Box>(Point3(130.0, 0.0, 65.0), Point3(295.0, 165.0, 230.0), materials.Get("WhiteDiffuse"));
                //auto box2 = std::make_shared<Box>(Point3(265.0, 0.0, 295.0), Point3(430.0, 330.0, 460.0), materials.Get("WhiteDiffuse"));
                //world.Add(std::make_shared<ConstantMedium>(box1, 0.01, materials.Get("IsotropicWhite")));
                //world.Add(std::make_shared<ConstantMedium>(box2, 0.01, materials.Get("IsotropicBlack")));

                world.Add(std::make_shared<Box>(Point3(130.0, 0.0, 65.0), Point3(295.0, 165.0, 230.0), materials.Get("WhiteDiffuse")));
                world.Add(std::make_shared<Box>(Point3(265.0, 0.0, 295.0), Point3(430.0, 330.0, 460.0), materials.Get("WhiteDiffuse")));

              // world.Add(std::make_shared<Sphere>(Point3(430.0, 82.5, 295.0), 82.5, materials.Get("WhiteDiffuse")));
               //world.Add(std::make_shared<Sphere>(Point3(150.0, 100.0, 295.0), 100.0, materials.Get("WhiteDiffuse")));
            }
            break;
        }
    }
} // namespace mortal
