#include "Hittable.hpp"
#include "Material.hpp"

bool Lambertian::scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const
{
    Vector3 scatterDirection = rec.normal + RandomUnitVector();

    // Catch degenerate scatter direction
    if (scatterDirection.nearZero()) scatterDirection = rec.normal;

    scattered = Ray(rec.p, scatterDirection);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const Ray& ray, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vector3 reflected = reflect(ray.direction(), rec.normal);
    reflected = UnitVector(reflected) + (fuzz * RandomUnitVector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return Dot(scattered.direction(), rec.normal) > 0;
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& rec, Color& attenuation,
                         Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

    Vector3 unitDirection = UnitVector(ray.direction());
    double cosTheta = std::fmin(Dot(-unitDirection, rec.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = ri * sinTheta > 1.0;
    Vector3 direction;

    if (cannotRefract || reflectance(cosTheta, ri) > RandomDouble())
        direction = reflect(unitDirection, rec.normal);
    else
        direction = refract(unitDirection, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
}
