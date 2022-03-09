#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Matrix3.hpp"
#include "support.hpp"

class Camera
{
public:
    Camera(sf::Vector3f position, sf::Vector3f origin,
           sf::Vector2f tileSize, float gridSize);

    const sf::Vector3f &getPosition() const;
    void setPosition(const sf::Vector3f &position);

    void pan(const sf::Vector2f &direction);
    void pan(const float &x, const float &y);

    sf::Vector3f transform(const sf::Vector3f &point) const;
    sf::Vector3f itransform(const sf::Vector3f &point) const;

    sf::Vector3f projectGround(const sf::Vector3f &point) const;
    sf::Vector3f projectGround(const sf::Vector2i &point) const;
private:
    sf::Vector3f position_;
    sf::Vector3f origin_;
    sf::Vector2f tileSize_;
    sf::Vector3f groundNormal_;
    float gridSize_;

    Matrix3 transformMatrix_;
    Matrix3 inverseMatrix_;
    sf::Vector3f translation_;

    sf::Vector3f cameraDirection_;
    sf::Vector3f cameraDirectionInv_;

    void calculateTranslation_();
};

#endif // __CAMERA_H__