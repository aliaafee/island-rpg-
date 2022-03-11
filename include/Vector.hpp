#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

using Vector3f = sf::Vector3f;
using Vector2f = sf::Vector2f;
using Vector2i = sf::Vector2i;

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")" ;
    return os;
}

float dotProduct(const Vector3f &a, const Vector3f &b);

void vecNormalize(Vector3f &v);
float vecMagnitude(const Vector3f &v);
float vecMagnitude2(const Vector3f &v);

bool intersetPlane(const Vector3f &n, const Vector3f &p0,
                   const Vector3f &l0, const Vector3f &l,
                   Vector3f *i);


#endif // __VECTOR_H__