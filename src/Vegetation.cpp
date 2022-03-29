#include "Vegetation.hpp"

TropicalTree::TropicalTree(ResourceManager &rm, RandomGenerator &r) : SpriteEntity(rm)
{
    std::vector<std::string> types = {"01", "03", "03", "03", "04", "04", "04", "11", "12"};
    std::string n = r.randomChoice(types);
    std::string filename = "graphics/sprites/_tree_" + n + "_" + std::to_string(r.randomInt(0, 7)) + "0000.sprite";

    // std::string filename = "graphics/sprites/_tree_01_00000.sprite";
    loadSprite(filename);

    // setTexture(rm.loadTexture(filename));

    // sf::FloatRect rect = getSpriteRect();

    // setSpriteOrigin(rect.width / 2.f, rect.height - 60.f);
    // setSize(5, 5, 5);
}