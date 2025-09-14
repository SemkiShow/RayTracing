#pragma once

#include "Hittable.hpp"

class Sphere : public Hittable
{
  public:
    Sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
    {
        Vector3 oc = center - r.origin();
        double a = r.direction().lengthSquared();
        double h = Dot(r.direction(), oc);
        double c = oc.lengthSquared() - radius * radius;

        double discriminant = h * h - a * c;
        if (discriminant < 0) return false;

        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vector3 outwardNormal = (rec.p - center) / radius;
        rec.SetFaceNormal(r, outwardNormal);

        return true;
    }

  private:
    Point3 center;
    double radius;
};
