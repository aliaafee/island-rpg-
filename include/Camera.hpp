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
           Vector2f tileSize, float gridSize);

    const Vector3f &getPosition() const;
    void setPosition(const Vector3f &position);

    void pan(const Vector2f &direction);
    void pan(const float &x, const float &y);

    Vector3f transform(const Vector3f &point) const;
    Vector3f itransform(const Vector3f &point) const;

    Vector3f projectGround(const Vector3f &point) const;
    Vector3f projectGround(const Vector2i &point) const;
private:
    Vector3f position_;
    Vector3f origin_;
    Vector2f tileSize_;
    Vector3f groundNormal_;
    float gridSize_;

    Matrix4 displaceMatrix_;
    Matrix4 transformMatrix_;
    Matrix4 inverseDisplace_;
    Matrix4 inverseTransform_;
    Vector3f translation_;

    Vector3f cameraDirection_;
    Vector3f cameraDirectionInv_;

    void updateTransforms_();
};

#endif // __CAMERA_H__