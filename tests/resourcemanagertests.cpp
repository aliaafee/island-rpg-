#include "../src/ResourceManager.h"

int main()
{
    std::cout << "Testing Resource Manager" <<std::endl;

    ResourceManager mngr;

    sf::Texture * tex = mngr.loadTexture("graphics/test/player.png");

    sf::Texture * tex2 = mngr.loadTexture("graphics/test/player.png");

    return 0;
}