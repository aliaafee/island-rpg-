#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <SFML/System.hpp>
#include <iostream>

using Vector3f = sf::Vector3f;
using Vector2f = sf::Vector2f;

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")" ;
    return os;
}


#endif // __VECTOR_H__