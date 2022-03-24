#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <deque>

#include "Vector.hpp"
#include "AnimatedEntity.hpp"
#include "ResourceManager.hpp"
#include "StateMachine2.hpp"
#include "World.hpp"

DEFINE_STATE_EVENTS(Player,
                    PLAYER_WALK_TARGET,
                    PLAYER_STOP);

class PlayerIdleState;
class PlayerWalkToState;
class PlayerWalkState;
class PlayerJumpState;

class Player : public AnimatedEntity
{
public:
    Player(ResourceManager &rm);
    ~Player();

    virtual void update(sf::Time &elapsed, World &world);

    void walkTo(const Vector3f &target);
    void walkPath(const std::deque<Vector3f> &path);
    void stop();

private:
    float walkSpeed_ = 1.f;

    float vertSpeed = 0;
    int jumpCount = 0;

    enum StateEvent
    {
        WALK_TO_TARGET,
        STOP
    };

    STATE_MACHINE(Player, World)
    statemachine_;

    STATE_INSTANCE(PlayerIdleState);
    STATE_INSTANCE(PlayerWalkState);
    STATE_INSTANCE(PlayerWalkToState);
    STATE_INSTANCE(PlayerJumpState);

    Vector3f walkTarget_;
    std::deque<Vector3f> walkPath_;

    std::string animationDirection_;
    std::string animationAction_;

    void setAnimationDirection(const std::string &direction);
    void setAnimationDirection(const Vector3f &direction);
    void setAnimationAction(const std::string &action);
};

DECLARE_STATE_CLASS(Player, World);

class PlayerIdleState : public STATE_CLASS(Player)
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

class PlayerWalkState : public STATE_CLASS(Player)
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

class PlayerJumpState : public PlayerWalkState
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

class PlayerWalkToState : public STATE_CLASS(Player)
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

#endif // __PLAYER_H__