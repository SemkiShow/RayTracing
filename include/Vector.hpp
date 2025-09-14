#pragma once

#include "Utils.hpp"
#include <cmath>
#include <iostream>

class Vector3
{
  public:
    double e[3];

    Vector3() : e{0, 0, 0} {}
    Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vector3& operator+=(const Vector3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vector3& operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vector3& operator/=(double t) { return *this *= 1 / t; }

    double length() const { return std::sqrt(lengthSquared()); }

    double lengthSquared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    bool nearZero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        double s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    static Vector3 random() { return Vector3(RandomDouble(), RandomDouble(), RandomDouble()); }

    static Vector3 random(double min, double max)
    {
        return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }
};

using Point3 = Vector3;

inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(double t, const Vector3& v)
{
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3& v, double t) { return t * v; }

inline Vector3 operator/(const Vector3& v, double t) { return (1 / t) * v; }

inline double Dot(const Vector3& u, const Vector3& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                   u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector3 UnitVector(const Vector3& v) { return v / v.length(); }

inline Vector3 RandomUnitVector()
{
    while (true)
    {
        Vector3 p = Vector3::random(-1, 1);
        double lensq = p.lengthSquared();
        if (1e-160 < lensq && lensq <= 1) return p / sqrt(lensq);
    }
}

inline Vector3 RandomOnHemisphere(const Vector3& normal)
{
    Vector3 onUnitSphere = RandomUnitVector();
    if (Dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
        return onUnitSphere;
    else
        return -onUnitSphere;
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) { return v - 2 * Dot(v, n) * n; }

inline Vector3 refract(const Vector3& uv, const Vector3& n, double etaiOverEtat)
{
    double cosTheta = std::fmin(Dot(-uv, n), 1.0);
    Vector3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
    Vector3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;
    return rOutPerp + rOutParallel;
}
