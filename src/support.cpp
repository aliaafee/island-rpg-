#include "support.hpp"

float dotProduct(const sf::Vector3f &a, const sf::Vector3f &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vecNormalize(sf::Vector3f &v)
{
    float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (mag == 0.f)
        return;
    v.x = v.x / mag;
    v.y = v.y / mag;
    v.z = v.z / mag;
}

float vecMagnitude(const sf::Vector3f &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vecMagnitude2(const sf::Vector3f &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

bool intersetPlane(const sf::Vector3f &n, const sf::Vector3f &p0,
                   const sf::Vector3f &l0, const sf::Vector3f &l,
                   sf::Vector3f *i)
{
    float denom = dotProduct(n, l);

    if (denom <= 0.0f)
        return false;

    sf::Vector3f p0l0 = p0 - l0;
    float t = dotProduct(p0l0, n) / denom;
    *i = l0 + (l * t);
    return true;
}