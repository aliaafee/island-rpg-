#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <deque>
#include <cmath>

#include "Vector.hpp"
#include "AnimatedEntity.hpp"
#include "ResourceManager.hpp"
#include "StateMachine2.hpp"
#include "World.hpp"

DEFINE_STATE_EVENTS(Player,
                    PLAYER_WALK_TARGET,
                    PLAYER_STOP,
                    PLAYER_ATTACK_OTHER,
                    PLAYER_REST);

class PlayerIdleState;
class PlayerRestingState;
class PlayerWalkToState;
class PlayerWalkState;
class PlayerJumpState;
class PlayerAttackingState;

class Player : public AnimatedEntity
{
public:
    Player(ResourceManager &rm);
    ~Player();

    virtual void update(sf::Time &elapsed, World &world);

    virtual void drawReflection(sf::RenderTarget *screen);

    void walkTo(const Vector3f &target);
    void walkPath(const std::deque<Vector3f> &path);
    void stop();
    void attackOther(Entity &entity);
    void rest();

    void setInWater(bool in);

private:
    float walkSpeed_ = 1.f;

    float jumpDelay = 0.f;
    float vertSpeed = 0;
    int jumpCount = 0;

    bool inWater = false;

    enum StateEvent
    {
        WALK_TO_TARGET,
        STOP
    };

    STATE_MACHINE(Player, World)
    statemachine_;

    STATE_INSTANCE(PlayerIdleState);
    STATE_INSTANCE(PlayerRestingState);
    STATE_INSTANCE(PlayerWalkState);
    STATE_INSTANCE(PlayerWalkToState);
    STATE_INSTANCE(PlayerJumpState);
    STATE_INSTANCE(PlayerAttackingState);

    Vector3f walkTarget_;
    std::deque<Vector3f> walkPath_;

    std::string animationDirection_;
    std::string animationAction_;

    Entity *attackingTarget_;

    void setAnimationDirection(const std::string &direction);
    void setAnimationDirection(const Vector3f &direction);
    void setAnimationAction(const std::string &action);

    std::string getAnimationName(const std::string &action, const std::string &direction);
};

DECLARE_STATE_CLASS(Player, World);

class PlayerIdleState : public STATE_CLASS(Player)
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

class PlayerRestingState : public PlayerIdleState
{
public:
    STATE_ENTER(Player, World);
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

class PlayerAttackingState : public PlayerWalkToState
{
public:
    STATE_ENTER(Player, World);
    STATE_UPDATE(Player, World);
};

#endif // __PLAYER_H__