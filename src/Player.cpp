#include "Player.hpp"

Player::Player(ResourceManager *rm) : AnimatedActor(rm)
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
    
    setCurrentAnimation("left_walking");
    setAnimationSpeed(10);
}

void Player::update(sf::Time &elapsed, World &world)
{
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
