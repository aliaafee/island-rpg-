#include "TrackingCamera.hpp"

TrackingCamera::TrackingCamera(Vector3f position, Vector3f origin,
                               Vector2f tileSize, float gridSize,
                               float windowWidth, float windowHeight) : Camera(position, origin,
                                                                               tileSize, gridSize,
                                                                               windowWidth, windowHeight),
                                                                        statemachine_(this),
                                                                        trackTarget_(nullptr)
{
    idleStateId = statemachine_.addState(&TrackingCamera::idleState);
    trackingStateId = statemachine_.addState(&TrackingCamera::trackingState);
}

void TrackingCamera::update(sf::Time &elapsed)
{
    statemachine_.updateState(elapsed, cameraData_);
}

StateId TrackingCamera::idleState(bool firstRun, sf::Time &elapsed, int &data)
{
    if (trackTarget_ != nullptr)
    {
        if (vecDistance2(getPosition(), trackTarget_->getPosition()) > maxDistance2_)
        {
            return trackingStateId;
        }
    }
    return idleStateId;
}

StateId TrackingCamera::trackingState(bool firstRun, sf::Time &elapsed, int &data)
{
    if (vecDistance2(getPosition(), trackTarget_->getPosition()) < minDistance2_)
    {
        return idleStateId;
    }

    // setPosition(trackTarget_->getPosition() * 0.02f + getPosition() * 0.98f);
    move((trackTarget_->getPosition() - getPosition()) * trackSpeed_ * elapsed.asSeconds());

    return trackingStateId;
}