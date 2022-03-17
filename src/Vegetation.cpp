#include "Vegetation.hpp"

Tree::Tree(ResourceManager &rm) : SpriteEntity(rm)
{
    std::string n = std::to_string(randi(1, 14));
    n.insert(n.begin(), 2 - n.size(), '0');
    std::string filename = "graphics/vegetation/_tree_" + n + "_" + std::to_string(randi(0, 7)) + "0000.png";

    setTexture(rm.loadTexture(filename));

    sf::FloatRect r = getSpriteRect();

    setSpriteOrigin(r.width / 2.f, r.height - 60.f);
    setSize(5, 5, 5);
}

Palm::Palm(ResourceManager &rm) : SpriteEntity(rm)
{
    std::string n = std::to_string(randi(1, 14));
    n.insert(n.begin(), 2 - n.size(), '0');
    std::string filename = "graphics/vegetation/_tree_" + n + "_" + std::to_string(randi(0, 7)) + "0000.png";

    setTexture(rm.loadTexture(filename));

    sf::FloatRect r = getSpriteRect();

    setSpriteOrigin(r.width / 2.f, r.height - 20.f);
    setSize(5, 5, 5);
}
