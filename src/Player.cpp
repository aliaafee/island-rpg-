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

void Player::walkTo(const sf::Vector3f &target)
{
    walkTarget_ = target;
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

    float stepSize = 1.5f * 60.f * elapsed.asSeconds();

    float distance = vecMagnitude(walkTarget_ - getPosition());
    if (distance < stepSize)
    {
        setPosition(walkTarget_);
        return idleStateId;
    }

    sf::Vector3f direction = (walkTarget_ - getPosition()) / distance;

    setAnimationDirection(direction);
    move(direction * stepSize);

    return walkStateId;
}

void Player::setAnimationDirection(const std::string &direction)
{
    animationDirection_ = direction;
    setCurrentAnimation(animationDirection_ + "_" + animationAction_);
}

void Player::setAnimationDirection(const sf::Vector3f &direction)
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
