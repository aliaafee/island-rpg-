#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <SFML/System.hpp>

float dotProduct(const sf::Vector3f &a, const sf::Vector3f &b);

bool intersetPlane(const sf::Vector3f &n, const sf::Vector3f &p0,
                    const sf::Vector3f &l0, const sf::Vector3f &l,
                    sf::Vector3f *i);

#endif // __SUPPORT_H__