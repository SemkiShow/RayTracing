#pragma once

#include "Hittable.hpp"
#include <memory>
#include <vector>

class HittableList : public Hittable
{
  public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    bool hit(const Ray& ray, Interval ray_t, HitRecord& rec) const override
    {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = ray_t.max;

        for (const auto& object: objects)
        {
            if (object->hit(ray, Interval(ray_t.min, closestSoFar), tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};
