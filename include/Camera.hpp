#pragma once

#include "Color.hpp"
#include "Hittable.hpp"
#include <fstream>

class Camera
{
  public:
    double aspectRatio = 16.0 / 9;
    int imageHeight = 480;
    int samplesPerPixel = 10;

    void render(const Hittable& world)
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
                    color += RayColor(ray, world);
                }
                WriteColor(output, pixelSamplesScale * color);
            }
        }
        std::clog << "\rDone.                 \n";
        output.close();
    }

  private:
    int imageWidth;
    double pixelSamplesScale;
    Point3 cameraCenter;
    Point3 pixel00Location;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    void initialize()
    {
        // Image
        imageWidth = imageHeight * aspectRatio;
        imageHeight = std::max(1, imageHeight);

        // Determine viewport dimensions.
        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (imageWidth * 1.0 / imageHeight);
        pixelSamplesScale = 1.0 / samplesPerPixel;
        cameraCenter = Point3(0, 0, 0);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        Vector3 viewportU = Vector3(viewportWidth, 0, 0);
        Vector3 viewportV = Vector3(0, -viewportHeight, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        // Calculate the location of the upper left pixel.
        Vector3 viewportUpperLeft =
            cameraCenter - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
    }

    Ray GetRay(int i, int j) const
    {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = SampleSquare();
        auto pixelSample =
            pixel00Location + ((j + offset.x()) * pixelDeltaU) + ((i + offset.y()) * pixelDeltaV);

        auto rayOrigin = cameraCenter;
        auto rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    Vector3 SampleSquare() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Vector3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
    }

    Color RayColor(const Ray& ray, const Hittable& world) const
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
};
