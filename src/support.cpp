#include "support.h"

float dotProduct(const sf::Vector3f &a, const sf::Vector3f &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
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