#include "TrackingCamera.hpp"

STATE_INSTANCE_INIT(TrackingCamera, CameraIdleState);
STATE_INSTANCE_INIT(TrackingCamera, CameraTrackingState);

TrackingCamera::TrackingCamera(Vector3f position,
                               Vector3f origin,
                               Vector2f tileSize,
                               float gridSize,
                               float windowWidth,
                               float windowHeight) : Camera(position, origin,
                                                            tileSize, gridSize,
                                                            windowWidth, windowHeight),
                                                     statemachine_(this, STATE(TrackingCamera, CameraIdleState)),
                                                     trackTarget_(nullptr)
{
}

void TrackingCamera::update(sf::Time &elapsed)
{
    statemachine_.updateState(elapsed, cameraData_);
}

STATE_UPDATE_FUNCTION(TrackingCamera, CameraIdleState, int, data)
{
    if (t->trackTarget_ != nullptr)
    {
        if (vecDistance2(t->getPosition(), t->trackTarget_->getPosition()) > t->maxDistance2_)
        {
            return STATE(TrackingCamera, CameraTrackingState);
        }
    }
    return nullptr;
}

STATE_UPDATE_FUNCTION(TrackingCamera, CameraTrackingState, int, data)
{
    if (vecDistance2(t->getPosition(), t->trackTarget_->getPosition()) < t->minDistance2_)
    {
        return STATE(TrackingCamera, CameraIdleState);
    }

    // setPosition(trackTarget_->getPosition() * 0.02f + getPosition() * 0.98f);
    t->move((t->trackTarget_->getPosition() - t->getPosition()) * t->trackSpeed_ * elapsed.asSeconds());

    return nullptr;
}