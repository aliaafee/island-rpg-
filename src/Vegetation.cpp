#include "Vegetation.hpp"

Tree::Tree(ResourceManager &rm, RandomGenerator &r) : SpriteEntity(rm)
{
    std::string n = std::to_string(r.randomInt(1, 14));
    n.insert(n.begin(), 2 - n.size(), '0');
    std::string filename = "graphics/vegetation/_tree_" + n + "_" + std::to_string(r.randomInt(0, 7)) + "0000.png";

    setTexture(rm.loadTexture(filename));

    sf::FloatRect rect = getSpriteRect();

    setSpriteOrigin(rect.width / 2.f, rect.height - 60.f);
    setSize(5, 5, 5);
}

Palm::Palm(ResourceManager &rm, RandomGenerator &r) : SpriteEntity(rm)
{
    std::string n = std::to_string(r.randomInt(1, 14));
    n.insert(n.begin(), 2 - n.size(), '0');
    std::string filename = "graphics/vegetation/_tree_" + n + "_" + std::to_string(r.randomInt(0, 7)) + "0000.png";

    setTexture(rm.loadTexture(filename));

    sf::FloatRect rect = getSpriteRect();

    setSpriteOrigin(rect.width / 2.f, rect.height - 20.f);
    setSize(5, 5, 5);
}
