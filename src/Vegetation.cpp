#include "Vegetation.hpp"

Tree::Tree(ResourceManager &rm) : SpriteEntity(rm)
{
    setTexture(rm.loadTexture("graphics/vegetation/tree01.png"));

    sf::FloatRect r = getSpriteRect();

    setSpriteOrigin(r.width / 2.f, r.height - 60.f);
    setSize(5, 5, 5);
}

Palm::Palm(ResourceManager &rm) : SpriteEntity(rm)
{
    setTexture(rm.loadTexture("graphics/vegetation/palm01.png"));

    sf::FloatRect r = getSpriteRect();

    setSpriteOrigin(r.width / 2.f, r.height - 20.f);
    setSize(5, 5, 5);
}
