#include "Player.hpp"

Player::Player(ResourceManager *rm) : AnimatedActor(rm),
                                      statemachine_(this)
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

    setCurrentAnimation("left_idle");
    setAnimationSpeed(10);
}

void Player::update(sf::Time &elapsed, World &world)
{
    statemachine_.updateState(world);
    animate(elapsed);

    // for (auto &actor : world.getActors())
    // {
    //     if (actor == this)
    //     {
    //         std::cout << "found myself " << typeid(*actor).name() << "\n";
    //         if (typeid(*actor) == typeid(Player))
    //         {
    //             std::cout << "Type matcher Player"
    //                       << "\n";
    //         }
    //     }
    // }
}

StateId Player::idleState(bool firstRun, World &world)
{
    if (firstRun)
    {
        testCounter = 0;
        std::cout << "Player to Idle State" << std::endl;
        setCurrentAnimation("left_idle");
    }

    testCounter += 1;
    std::cout << "idling " << testCounter << "\n";
    if (testCounter > 200)
    {
        return walkStateId;
    }
    return idleStateId;
}

StateId Player::walkState(bool firstRun, World &world)
{
    if (firstRun)
    {
        testCounter = 0;
        std::cout << "Player to Walk State" << std::endl;
        setCurrentAnimation("left_walking");
    }
    testCounter += 1;
    std::cout << "walking " << testCounter << "\n";
    if (testCounter > 200)
    {
        return idleStateId;
    }
    return walkStateId;
}
