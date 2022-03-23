#ifndef __TRACKINGCAMERA_H__
#define __TRACKINGCAMERA_H__

#include "Entity.hpp"
#include "Camera.hpp"
#include "StateMachine2.hpp"

DEFINE_STATE_EVENTS(TrackingCamera,
                    CAMERA_STOP);

class CameraIdleState;
class CameraTrackingState;

class TrackingCamera : public Camera
{
public:
    TrackingCamera(Vector3f position, Vector3f origin,
                   Vector2f tileSize, float gridSize,
                   float windowWidth, float windowHeight);

    virtual void update(sf::Time &elapsed);

    void setTrackTarget(Entity &entity, const float &trackSpeed, const float &minDistance, const float &maxDistance)
    {
        trackTarget_ = &entity;
        trackSpeed_ = trackSpeed;
        minDistance2_ = minDistance * minDistance;
        maxDistance2_ = maxDistance * maxDistance;
    }

private:
    enum StateEvent
    {
        DEFAULT
    };

    STATE_MACHINE(TrackingCamera, int)
    statemachine_;

    int cameraData_;

    STATE_INSTANCE(CameraIdleState);
    STATE_INSTANCE(CameraTrackingState);

    Entity *trackTarget_;
    float minDistance2_;
    float maxDistance2_;
    float trackSpeed_;
};

DECLARE_STATE_CLASS(TrackingCamera, int);

class CameraIdleState : public STATE_CLASS(TrackingCamera)
{
public:
    STATE_UPDATE(TrackingCamera, int);
};

class CameraTrackingState : public STATE_CLASS(TrackingCamera)
{
public:
    STATE_UPDATE(TrackingCamera, int);
};

#endif // __TRACKINGCAMERA_H__