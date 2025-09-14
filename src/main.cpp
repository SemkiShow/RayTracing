#include "Color.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Interval.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"
#include <fstream>

Color RayColor(const Ray& ray, const Hittable& world)
{
    HitRecord rec;
    if (world.hit(ray, Interval(0, infinity), rec))
    {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vector3 unitDirection = UnitVector(ray.direction());
    double a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    double aspectRatio = 16.0 / 9;
    int imageHeight = 480;
    int imageWidth = imageHeight * aspectRatio;
    imageHeight = std::max(1, imageHeight);

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (imageWidth * 1.0 / imageHeight);
    Point3 cameraCenter = Point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewportU = Vector3(viewportWidth, 0, 0);
    Vector3 viewportV = Vector3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel.
    Vector3 viewportUpperLeft =
        cameraCenter - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    Vector3 pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    std::ofstream output("image.ppm");
    output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++)
        {
            Vector3 pixelCenter = pixel00Location + (j * pixelDeltaU) + (i * pixelDeltaV);
            Vector3 rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            Color color = RayColor(ray, world);
            WriteColor(output, color);
        }
    }
    std::clog << "\rDone.                 \n";
    output.close();
}
