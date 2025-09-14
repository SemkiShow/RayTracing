#pragma once

#include "Ray.hpp"
#include "Interval.hpp"

class HitRecord
{
  public:
    Point3 p;
    Vector3 normal;
    double t;
    bool frontFace;

    void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal)
    {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        frontFace = Dot(ray.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& rec) const = 0;
};
