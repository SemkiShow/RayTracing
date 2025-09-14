#include "Camera.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"

int main()
{
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageHeight = 480;
    camera.samplesPerPixel = 100;

    camera.render(world);
}
