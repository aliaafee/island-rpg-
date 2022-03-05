#include "camera.h"

Camera::Camera(sf::Vector3f position, sf::Vector3f origin, sf::Vector2f tileSize, float gridSize)
{
    _origin = origin;
    _position = position;
    _tileSize = tileSize;
    _gridSize = gridSize;

    _groundNormal = sf::Vector3f(0, 0, 1);
    _cameraDirection = sf::Vector3f(0, 0, 1);

    float w_h = _tileSize.x / 2;
    float h_h = _tileSize.y / 2;
    float l = w_h / cos(45 / 180 * M_PI);
    sf::Vector3f s = sf::Vector3f(gridSize, gridSize, gridSize);

    _transformMatrix = Matrix3(
                               w_h / s.x,                   -1 * w_h / s.y,            0,
                               h_h / s.x,                        h_h / s.y, -1 * l / s.z,
        w_h * tan(45 / 180 * M_PI) / s.x, w_h * tan(45 / 180 * M_PI) / s.y,            0    );

    _inverseMatrix = _transformMatrix.getInverse();

    _cameraDirectionInv = _inverseMatrix * _cameraDirection;

    _calculateTranslation();
}

const sf::Vector3f& Camera::getPosition() const
{
    return _position;
}

void Camera::setPosition(const sf::Vector3f &position)
{
    _position = position;
    _calculateTranslation();
}

const sf::Vector3f Camera::transform(const sf::Vector3f &point)
{
    return (_transformMatrix * point) + _translation;
}

const sf::Vector3f Camera::itransform(const sf::Vector3f &point)
{
    return _inverseMatrix * (point - _translation);
}

void Camera::_calculateTranslation()
{
    _translation = _origin - (_transformMatrix * _position);
}
