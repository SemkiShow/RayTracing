#pragma once

#include "Color.hpp"
#include "Ray.hpp"

class HitRecord;

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
                 Ray& scattered) const override;

  private:
    Color albedo;
};

class Metal : public Material
{
  public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz > 1 ? fuzz : 1) {}

    bool scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override;

  private:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material
{
  public:
    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                 Ray& scattered) const override;

  private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refractionIndex;

    static double reflectance(double cosine, double refractionIndex)
    {
        // Use Schlick's approximation for reflectance.
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};
