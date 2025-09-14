#include "Camera.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Scenes.hpp"
#include "Sphere.hpp"

void Scene1()
{
    HittableList world;

    auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<Dielectric>(1.50);
    auto materialBubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materialBubble));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageHeight = 480;
    camera.samplesPerPixel = 10;
    camera.maxDepth = 50;
    camera.vfov = 20;
    camera.lookfrom = Point3(-2, 2, 1);
    camera.lookat = Point3(0, 0, -1);
    camera.vup = Vector3(0, 1, 0);
    camera.defocusAngle = 10.0;
    camera.focusDistance = 3.4;

    camera.render(world);
}

void Scene2()
{
    HittableList world;

    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            auto choose_mat = RandomDouble();
            Point3 center(i + 0.9 * RandomDouble(), 0.2, j + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageHeight = 1200;
    camera.samplesPerPixel = 10;
    camera.maxDepth = 50;
    camera.vfov = 20;
    camera.lookfrom = Point3(13, 2, 3);
    camera.lookat = Point3(0, 0, 0);
    camera.vup = Vector3(0, 1, 0);
    camera.defocusAngle = 0.6;
    camera.focusDistance = 10.0;

    camera.render(world);
}

void Render(int sceneID)
{
    if (sceneID == 1)
        Scene1();
    else if (sceneID == 2)
        Scene2();
    else
        std::cerr << "Invalid scene ID!\n";
}
