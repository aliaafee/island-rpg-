#include "SpriteActor.h"


SpriteActor::SpriteActor() : Actor()
{
    if (!texture_.loadFromFile("graphics/test/player.png"))
    {
        std::cout << "failed to load texture" << "\n";
        return;
    }
    std::cout << "Texture Loaded" << "\n";
    sprite_.setTexture(texture_);
    sprite_.setOrigin(32, 64);
}

SpriteActor::~SpriteActor()
{
    
}

void SpriteActor::update(World &world)
{
    //Actor::update(world);
    
}

void SpriteActor::transform(Camera &camera)
{
    Actor::transform(camera);
    sprite_.setPosition(getScreenPosition().x, getScreenPosition().y);
    
}

void SpriteActor::draw(sf::RenderTarget *screen)
{
    Actor::draw(screen);
    screen->draw(sprite_);
}
