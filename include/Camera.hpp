#pragma once

#include "Color.hpp"
#include "Hittable.hpp"

class Camera
{
  public:
    double aspectRatio = 16.0 / 9;
    int imageHeight = 480;
    int samplesPerPixel = 10;
    int maxDepth = 10;
    double vfov = 90;
    Point3 lookfrom = Point3(0, 0, 0);
    Point3 lookat = Point3(0, 0, -1);
    Vector3 vup = Vector3(0, 1, 0);

    void render(const Hittable& world);

  private:
    int imageWidth;
    double pixelSamplesScale;
    Point3 cameraCenter;
    Point3 pixel00Location;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    Vector3 u, v, w;

    void initialize();

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

    Color RayColor(const Ray& ray, int depth, const Hittable& world) const;
};
