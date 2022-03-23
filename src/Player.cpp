#include "Player.hpp"

STATE_INSTANCE_INIT(Player, PlayerIdleState);
STATE_INSTANCE_INIT(Player, PlayerWalkState);

Player::Player(ResourceManager &rm) : AnimatedEntity(rm),
                                      statemachine_(
                                          this,
                                          STATE(Player, PlayerIdleState)),
                                      animationDirection_("down"),
                                      animationAction_("idle")
{
    std::string animationNames[12] = {
        "up_walking", "down_walking", "left_walking", "right_walking",
        "up_idle", "down_idle", "left_idle", "right_idle",
        "up_attack", "down_attack", "left_attack", "right_attack"};

    std::string animationDirectory = "graphics/player/";

    for (auto &name : animationNames)
    {
        loadAnimation(name, animationDirectory + name);
    }

    setSpriteOrigin(32, 64);

    setAnimationSpeed(10);
}

void Player::update(sf::Time &elapsed, World &world)
{
    statemachine_.updateState(elapsed, world);

    animate(elapsed);
}

void Player::walkTo(const Vector3f &target)
{
    walkTarget_ = target;
    statemachine_.queueEvent(PLAYER_WALK_TARGET);
}

void Player::walkPath(const std::deque<Vector3f> &path)
{
    walkPath_ = path;
    statemachine_.queueEvent(PLAYER_WALK_TARGET);
}

void Player::stop()
{
    statemachine_.queueEvent(PLAYER_STOP);
}

void Player::setAnimationDirection(const std::string &direction)
{
    animationDirection_ = direction;
    setCurrentAnimation(animationDirection_ + "_" + animationAction_);
}

void Player::setAnimationDirection(const Vector3f &direction)
{
    if (direction.x >= 0.f && direction.y < 0.f)
    {
        setAnimationDirection("right");
        return;
    }
    else if (direction.x >= 0.f && direction.y >= 0.f)
    {
        setAnimationDirection("down");
        return;
    }
    else if (direction.x < 0 && direction.y >= 0)
    {
        setAnimationDirection("left");
        return;
    }
    setAnimationDirection("up");
    return;
}

void Player::setAnimationAction(const std::string &action)
{
    animationAction_ = action;
    setCurrentAnimation(animationDirection_ + "_" + animationAction_);
}

STATE_ENTER_FUNCTION(Player, PlayerIdleState, World, world)
{
    std::cout << "Player to Idle State" << std::endl;
    t->setAnimationAction("idle");
}

STATE_UPDATE_FUNCTION(Player, PlayerIdleState, World, world)
{
    POLL_STATE_EVENTS(Player)
    {
        switch (event)
        {
        case PLAYER_WALK_TARGET:
            return STATE(Player, PlayerWalkState);
            break;
        default:
            break;
        }
    }

    return nullptr;
}

STATE_ENTER_FUNCTION(Player, PlayerWalkState, World, world)
{

    std::cout << "Player to Walk State" << std::endl;
    std::cout << "Finding Path.." << std::flush;
    t->walkPath_.clear();
    bool found = world.findPath(
        *t,
        t->walkTarget_,
        true,
        t->walkPath_);
    if (!found)
    {
        std::cout << "Not found\n";
        return;
    }
    std::cout << "Found\n";
    t->setAnimationAction("walking");
}

STATE_UPDATE_FUNCTION(Player, PlayerWalkState, World, world)
{
    POLL_STATE_EVENTS(Player)
    {
        switch (event)
        {
        case PLAYER_STOP:
            return STATE(Player, PlayerIdleState);
            break;
        case PLAYER_WALK_TARGET:
            std::cout << "Recalc Path.." << std::flush;
            t->walkPath_.clear();
            bool found = world.findPath(
                *t,
                t->walkTarget_,
                true,
                t->walkPath_);
            if (!found)
            {
                std::cout << "Not found\n";
            }
            else
            {
                std::cout << "Found\n";
            }
            break;
        }
    }

    if (t->walkPath_.empty())
    {
        return STATE(Player, PlayerIdleState);
    }

    float stepSize = 1.f * 60.f * elapsed.asSeconds();
    Vector3f position;

    float distance2 = vecMagnitude2(t->toLocal(t->walkPath_.front()) - t->getLocalPosition());
    if (distance2 > stepSize * stepSize)
    {
        float distance = sqrt(distance2);
        Vector3f direction = (t->toLocal(t->walkPath_.front()) - t->getLocalPosition()) / distance;

        t->setAnimationDirection(direction);
        position = t->getLocalPosition() + direction * stepSize;
    }
    else
    {
        position = t->toLocal(t->walkPath_.front());
        t->walkPath_.pop_front();
    }

    if (!world.canMoveTo(*t, position))
    {
        // walkPath_.clear();
        // bool found = world.findPath(
        //     *this,
        //     walkTarget_,
        //     true,
        //     walkPath_);
        // if (!found)
        // {
        //     std::cout << "Not found\n";
        //     return idleStateId;
        // }
        // return walkStateId;
        return STATE(Player, PlayerIdleState);
    }

    t->setLocalPosition(position);

    return nullptr;
}
