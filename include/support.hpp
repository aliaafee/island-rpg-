#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <cmath>
#include <SFML/System.hpp>

float dotProduct(const sf::Vector3f &a, const sf::Vector3f &b);

void vecNormalize(sf::Vector3f &v);
float vecMagnitude(const sf::Vector3f &v);
float vecMagnitude2(const sf::Vector3f &v);

bool intersetPlane(const sf::Vector3f &n, const sf::Vector3f &p0,
                   const sf::Vector3f &l0, const sf::Vector3f &l,
                   sf::Vector3f *i);

#endif // __SUPPORT_H__