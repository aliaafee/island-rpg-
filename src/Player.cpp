#include "Player.hpp"

Player::Player(ResourceManager *rm) : AnimatedActor(rm),
                                      statemachine_(this),
                                      animationDirection_("down"),
                                      animationAction_("idle")
{
    idleStateId = statemachine_.addState(&Player::idleState);
    walkStateId = statemachine_.addState(&Player::walkState);

    std::string animationNames[12] = {
        "up_walking", "down_walking", "left_walking", "right_walking",
        "up_idle", "down_idle", "left_idle", "right_idle",
        "up_attack", "down_attack", "left_attack", "right_attack"};

    std::string animationDirectory = "graphics/player/";

    for (auto &name : animationNames)
    {
        loadAnimation(name, animationDirectory + name);
    }

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
    statemachine_.queueEvent(WALK_TO_TARGET);
}

void Player::walkPath(const std::deque<Vector3f> &path)
{
    walkPath_ = path;
    statemachine_.queueEvent(WALK_TO_TARGET);
}

void Player::stop()
{
    statemachine_.queueEvent(STOP);
}

StateId Player::idleState(bool firstRun, sf::Time &elapsed, World &world)
{
    if (firstRun)
    {
        std::cout << "Player to Idle State" << std::endl;
        setAnimationAction("idle");
    }

    StateEvent event;
    while (statemachine_.pollEvent(event))
    {
        switch (event)
        {
        case WALK_TO_TARGET:
            return walkStateId;
            break;
        default:
            break;
        }
    }

    return idleStateId;
}

StateId Player::walkState(bool firstRun, sf::Time &elapsed, World &world)
{
    if (firstRun)
    {
        std::cout << "Player to Walk State" << std::endl;
        setAnimationAction("walking");
        std::cout << "Finding Path.." << std::flush;
        bool found = world.findPath(
            getPosition(),
            walkTarget_,
            true,
            walkPath_
        );
        if (!found)
        {
            std::cout << "Not found\n";
            return idleStateId;
        }
        std::cout << "Found\n";
    }

    StateEvent event;
    while (statemachine_.pollEvent(event))
    {
        switch (event)
        {
        case STOP:
            return idleStateId;
            break;
        default:
            break;
        }
    }

    if (walkPath_.empty())
    {
        return idleStateId;
    }

    float stepSize = 1.f * 60.f * elapsed.asSeconds();

    float distance2 = vecMagnitude2(walkPath_.front() - getPosition());
    if (distance2 < stepSize * stepSize)
    {
        setPosition(walkPath_.front());
        walkPath_.pop_front();
        return walkStateId;
    }

    float distance = sqrt(distance2);
    Vector3f direction = (walkPath_.front() - getPosition()) / distance;

    setAnimationDirection(direction);
    move(direction * stepSize);

    return walkStateId;
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
