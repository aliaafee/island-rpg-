#include "SpriteActor.hpp"

SpriteActor::SpriteActor(ResourceManager &rm) : Actor(rm)
{
}

SpriteActor::~SpriteActor()
{
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

void SpriteActor::setTexture(sf::Texture *texture)
{
    sprite_.setTexture(*texture);
}
