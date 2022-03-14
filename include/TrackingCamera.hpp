#ifndef __TRACKINGCAMERA_H__
#define __TRACKINGCAMERA_H__

#include "Entity.hpp"
#include "Camera.hpp"
#include "StateMachine.hpp"

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

    StateMachine<TrackingCamera, int, StateEvent> statemachine_;

    int cameraData_;

    StateId idleStateId;
    StateId trackingStateId;

    StateId idleState(bool firstRun, sf::Time &elapsed, int &data);

    Entity *trackTarget_;
    float minDistance2_;
    float maxDistance2_;
    float trackSpeed_;
    StateId trackingState(bool firstRun, sf::Time &elapsed, int &data);
};
#endif // __TRACKINGCAMERA_H__