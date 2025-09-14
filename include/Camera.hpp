#pragma once

#include "Color.hpp"
#include "Hittable.hpp"

class Camera
{
  public:
    double aspectRatio = 16.0 / 9;
    int imageHeight = 720;
    int imageWidth = 1280;
    double pixelSamplesScale = 1;
    int samplesPerPixel = 10;
    int maxDepth = 10;
    double vfov = 90;
    Point3 lookfrom = Point3(0, 0, 0);
    Point3 lookat = Point3(0, 0, -1);
    Vector3 vup = Vector3(0, 1, 0);
    double defocusAngle = 0;
    double focusDistance = 10;

    void render(const Hittable& world);

    Ray GetRay(int i, int j) const
    {
        // Construct a camera ray originating from the defocus disk and directed at a randomly
        // sampled point around the pixel location i, j.

        Vector3 offset = SampleSquare();
        Vector3 pixelSample =
            pixel00Location + ((j + offset.x()) * pixelDeltaU) + ((i + offset.y()) * pixelDeltaV);

        Point3 rayOrigin = (defocusAngle <= 0) ? cameraCenter : DefocusDiskSample();
        Vector3 rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    Color RayColor(const Ray& ray, int depth, const Hittable& world) const;

  private:
    Point3 cameraCenter;
    Point3 pixel00Location;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    Vector3 u, v, w;
    Vector3 defocusDiskU;
    Vector3 defocusDiskV;

    void initialize();

    Vector3 SampleSquare() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Vector3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
    }

    Point3 DefocusDiskSample() const
    {
        // Returns a random point in the camera defocus disk.
        Vector3 p = RandomInUnitDisk();
        return cameraCenter + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
    }
};
