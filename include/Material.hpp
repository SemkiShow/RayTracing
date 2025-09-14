#pragma once

#include "Color.hpp"
#include "Hittable.hpp"

class Material
{
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const
    {
        return false;
    }
};

class Lambertian : public Material
{
  public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        Vector3 scatterDirection = rec.normal + RandomUnitVector();

        // Catch degenerate scatter direction
        if (scatterDirection.nearZero()) scatterDirection = rec.normal;

        scattered = Ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    }

  private:
    Color albedo;
};

class Metal : public Material
{
  public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz > 1 ? fuzz : 1) {}

    bool scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override
    {
        Vector3 reflected = reflect(ray.direction(), rec.normal);
        reflected = UnitVector(reflected) + (fuzz * RandomUnitVector());
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return Dot(scattered.direction(), rec.normal) > 0;
    }

  private:
    Color albedo;
    double fuzz;
};
