#include "Camera.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"

int main()
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

    camera.render(world);
}
