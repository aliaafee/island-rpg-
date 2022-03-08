#include "Player.hpp"

Player::Player(ResourceManager *rm) : AnimatedActor(rm),
                                      statemachine_(this, "idle"),
                                      idleCT(0)
{
    statemachine_.addState("idle", &Player::idleState);
    statemachine_.addState("walk", &Player::walkState);

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
    statemachine_.updateState();
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

std::string Player::idleState(bool firstRun)
{
    if (firstRun)
    {
        std::cout << "Player to Idle State" << std::endl;
        setCurrentAnimation("left_idle");
    }
    idleCT += 1;
    if (idleCT > 200)
    {
        idleCT = 0;
        return "walk";
    }
    return "idle";
}

std::string Player::walkState(bool firstRun)
{
    if (firstRun)
    {
        std::cout << "Player to Walk State" << std::endl;
        setCurrentAnimation("left_walking");
    }
    return "walk";
}
