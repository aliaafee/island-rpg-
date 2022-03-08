#include "../src/ResourceManager.hpp"

int main()
{
    std::cout << "# Testing Resource Manager" << std::endl;

    ResourceManager mngr;

    sf::Texture *tex = mngr.loadTexture("graphics/test/player.png");

    sf::Texture *tex2 = mngr.loadTexture("graphics/test/player.png");

    std::vector<sf::Texture *> sequence;

    bool result = mngr.loadTextureDirectory("graphics/player/down_attack", &sequence);

    std::cout << sequence.size() << "\n";

    return 0;
}