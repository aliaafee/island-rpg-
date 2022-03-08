#include "Player.h"

Player::Player(ResourceManager *rm) : AnimatedActor(rm)
{
    loadAnimation("down_attack", "graphics/player/down_attack");
    loadAnimation("left_walking", "graphics/player/left_walking");
    setCurrentAnimation("left_walking");
    setAnimationSpeed(10);
}

void Player::update(sf::Time &elapsed, World &world)
{
    animate(elapsed);

    for (auto &actor : world.getActors())
    {
        if (actor == this)
        {
            std::cout << "found myself " << typeid(*actor).name() << "\n";
            if (typeid(*actor) == typeid(Player))
            {
                std::cout << "Type matcher Player"
                          << "\n";
            }
        }
    }
}
