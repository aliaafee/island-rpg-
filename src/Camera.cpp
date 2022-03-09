#include "Camera.hpp"

Camera::Camera(sf::Vector3f position,
               sf::Vector3f origin,
               sf::Vector2f tileSize,
               float gridSize) : position_(position),
                                 origin_(origin),
                                 tileSize_(tileSize),
                                 gridSize_(gridSize),
                                 groundNormal_(0, 0, 1),
                                 cameraDirection_(0, 0, 1)
{
    float w_h = tileSize_.x / 2.0;
    float h_h = tileSize_.y / 2.0;
    float l = w_h / cos((45.0 / 180.0) * M_PI);
    sf::Vector3f s = sf::Vector3f(gridSize_, gridSize_, gridSize_);

    transformMatrix_ = Matrix3(
        w_h / s.x, -1 * w_h / s.y, 0,
        h_h / s.x, h_h / s.y, -1 * l / s.z,
        w_h * tan((45.0 / 180.0) * M_PI) / s.x, w_h * tan((45.0 / 180.0) * M_PI) / s.y, 0);

    inverseMatrix_ = transformMatrix_.getInverse();

    cameraDirection_ = inverseMatrix_ * cameraDirection_;

    calculateTranslation_();
}

const sf::Vector3f &Camera::getPosition() const
{
    return position_;
}

void Camera::setPosition(const sf::Vector3f &position)
{
    position_ = position;
    calculateTranslation_();
}

void Camera::pan(const sf::Vector2f &direction)
{
    pan(direction.x, direction.y);
}

void Camera::pan(const float &x, const float &y)
{
    sf::Vector3f screenPosition = transform(position_);
    screenPosition.x += x;
    screenPosition.y += y;
    setPosition(projectGround(screenPosition));
}

sf::Vector3f Camera::transform(const sf::Vector3f &point) const
{
    return (transformMatrix_ * point) + translation_;
}

sf::Vector3f Camera::itransform(const sf::Vector3f &point) const
{
    return inverseMatrix_ * (point - translation_);
}

sf::Vector3f Camera::projectGround(const sf::Vector3f &point) const
{
    float groundElevation = 0;

    sf::Vector3f intPoint;
    bool intersected = intersetPlane(
        groundNormal_,
        sf::Vector3f(0, 0, groundElevation),
        itransform(point),
        cameraDirection_,
        &intPoint);

    return intPoint;
}

sf::Vector3f Camera::projectGround(const sf::Vector2i &point) const
{
    return projectGround(
        sf::Vector3f((float)point.x, (float)point.y, 0));
}

void Camera::calculateTranslation_()
{
    translation_ = origin_ - (transformMatrix_ * position_);
}
