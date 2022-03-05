#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <math.h>
#include <SFML/Graphics.hpp>

#include "matrix3.h"


class Camera
{
public:
    Camera(sf::Vector3f position, sf::Vector3f origin, sf::Vector2f tileSize, float gridSize);

    const sf::Vector3f &getPosition() const;
    void setPosition(const sf::Vector3f &position);

    const sf::Vector3f transform(const sf::Vector3f &point);
    const sf::Vector3f itransform(const sf::Vector3f &point);
private:
    sf::Vector3f _position;
    sf::Vector3f _origin;
    sf::Vector2f _tileSize;
    sf::Vector3f _groundNormal;
    float _gridSize;

    Matrix3 _transformMatrix;
    Matrix3 _inverseMatrix;
    sf::Vector3f _translation;

    sf::Vector3f _cameraDirection;
    sf::Vector3f _cameraDirectionInv;

    void _calculateTranslation();
};

#endif // __CAMERA_H__