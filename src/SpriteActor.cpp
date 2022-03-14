#include "SpriteEntity.hpp"

SpriteEntity::SpriteEntity(ResourceManager &rm) : Entity(rm)
{
}

SpriteEntity::~SpriteEntity()
{
}

void SpriteEntity::transform(Camera &camera)
{
    Entity::transform(camera);
    sprite_.setPosition(getScreenPosition().x, getScreenPosition().y);
}

void SpriteEntity::draw(sf::RenderTarget *screen)
{
    Entity::draw(screen);
    screen->draw(sprite_);
}

void SpriteEntity::setTexture(sf::Texture *texture)
{
    sprite_.setTexture(*texture);
}
