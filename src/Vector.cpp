#include "Vector.hpp"

float vecDotProd(const Vector3f &a, const Vector3f &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vecNormalize(Vector3f &v)
{
    float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (mag == 0.f)
        return;
    v.x = v.x / mag;
    v.y = v.y / mag;
    v.z = v.z / mag;
}

float vecMagnitude(const Vector3f &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vecMagnitude2(const Vector3f &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

bool vecNull(const Vector3f &v)
{
    if (v.x == 0.f && v.y == 0.f and v.z == 0.f)
        return true;
    return false;
}

float vecDistance(const Vector3f &a, const Vector3f &b)
{
    return vecMagnitude(b - a);
}

float vecDistance2(const Vector3f &a, const Vector3f &b)
{
    return vecMagnitude2(b - a);
}

bool intersetPlane(const Vector3f &n, const Vector3f &p0,
                   const Vector3f &l0, const Vector3f &l,
                   Vector3f *i)
{
    float denom = vecDotProd(n, l);

    if (denom <= 0.0f)
        return false;

    Vector3f p0l0 = p0 - l0;
    float t = vecDotProd(p0l0, n) / denom;
    *i = l0 + (l * t);
    return true;
}