#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#include "Matrix4.hpp"

class Camera
{
public:
    Camera(Vector3f position, Vector3f origin,
           Vector2f tileSize, float gridSize,
           float windowWidth, float windowHeight);

    const Vector3f &getPosition() const;
    void setPosition(const Vector3f &position);
    void setPosition(const float &x, const float &y, const float &z);
    void move(const Vector3f &velocity);
    void move(const float &x, const float &y, const float &z);

    void pan(const Vector2f &direction);
    void pan(const float &x, const float &y);

    void setZoom(const float &z);
    void zoom(const float &z) { setZoom(zoomFactor_ * z); }

    void rotate(const float &r) { rotation_ += r; }
    void setRotation(const float &r) { rotation_ = r; }

    void updateWindow(sf::RenderWindow &window);

    virtual void update(sf::Time &elapsed){};

    Vector3f transform(const Vector3f &point) const;
    Vector2f transform2(const Vector3f &point) const;

    Vector3f itransform(const Vector3f &point) const;

    Vector3f transform(const Vector3f &point, const float &w) const;
    Vector2f transform2(const Vector3f &point, const float &w) const;

    Vector3f itransform(const Vector3f &point, const float &w) const;

    Vector3f projectGround(const Vector3f &point) const;
    Vector3f projectGround(const Vector2f &point) const;
    Vector3f projectGround(const Vector2i &point) const;

private:
    Vector3f position_;
    Vector3f origin_;
    Vector2f tileSize_;
    Vector3f groundNormal_;
    float gridSize_;

    Matrix4 transformMatrix_;
    Matrix4 inverseTransform_;
    Vector3f translation_;

    Vector3f cameraDirection_;
    Vector3f cameraDirectionInv_;

    sf::View windowView_;
    float windowWidth_;
    float windowHeight_;
    float zoomFactor_;
    float maxZoom_;
    float minZoom_;
    float rotation_;

    void updateTransforms_();
};

#endif // __CAMERA_H__