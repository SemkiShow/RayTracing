#include "Camera.hpp"
#include "Material.hpp"
#include <fstream>

void Camera::render(const Hittable& world)
{
    initialize();

    std::ofstream output("image.ppm");
    output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++)
        {
            Color color(0, 0, 0);
            for (int k = 0; k < samplesPerPixel; k++)
            {
                Ray ray = GetRay(i, j);
                color += RayColor(ray, maxDepth, world);
            }
            WriteColor(output, pixelSamplesScale * color);
        }
    }
    std::clog << "\rDone.                 \n";
    output.close();
}

void Camera::initialize()
{
    // Image
    imageWidth = imageHeight * aspectRatio;
    imageHeight = std::max(1, imageHeight);

    // Determine viewport dimensions.
    double focalLength = (lookfrom - lookat).length();
    double theta = DegreesToRadians(vfov);
    double h = std::tan(theta / 2);
    double viewportHeight = 2 * h * focalLength;
    double viewportWidth = viewportHeight * (imageWidth * 1.0 / imageHeight);
    pixelSamplesScale = 1.0 / samplesPerPixel;
    cameraCenter = lookfrom;

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = UnitVector(lookfrom - lookat);
    u = UnitVector(Cross(vup, w));
    v = Cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewportU = viewportWidth * u;
    Vector3 viewportV = viewportHeight * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel.
    Vector3 viewportUpperLeft = cameraCenter - (focalLength * w) - viewportU / 2 - viewportV / 2;
    pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

Color Camera::RayColor(const Ray& ray, int depth, const Hittable& world) const
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) return Color(0, 0, 0);

    HitRecord rec;
    if (world.hit(ray, Interval(0.001, infinity), rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.mat->scatter(ray, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, depth - 1, world);
        return Color(0, 0, 0);
    }

    Vector3 unitDirection = UnitVector(ray.direction());
    double a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
