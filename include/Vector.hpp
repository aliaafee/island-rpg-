#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

using Vector3f = sf::Vector3f;
using Vector2f = sf::Vector2f;
using Vector2i = sf::Vector2i;
using Vector2u = sf::Vector2u;
using FloatRect = sf::FloatRect;

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

float vecDotProd(const Vector3f &a, const Vector3f &b);
void vecNormalize(Vector3f &v);
float vecMagnitude(const Vector3f &v);
float vecMagnitude2(const Vector3f &v);
bool vecNull(const Vector3f &v);
float vecDistance(const Vector3f &a, const Vector3f &b);
float vecDistance2(const Vector3f &a, const Vector3f &b);

bool intersetPlane(const Vector3f &n, const Vector3f &p0,
                   const Vector3f &l0, const Vector3f &l,
                   Vector3f *i);

inline sf::Color mixColor(sf::Color a, sf::Color b, float factor)
{
    factor = std::clamp(factor, 0.f, 1.f);
    Vector3f av(
        (float)a.r / 255.f,
        (float)a.g / 255.f,
        (float)a.b / 255.f);
    Vector3f bv(
        (float)b.r / 255.f,
        (float)b.g / 255.f,
        (float)b.b / 255.f);
    Vector3f r = (av + (bv - av) * factor) * 255.f;
    return sf::Color(
        (int)r.x,
        (int)r.y,
        (int)r.z,
        a.a);
}

#endif // __VECTOR_H__