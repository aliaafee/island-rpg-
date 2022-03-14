#ifndef __SPRITEACTOR_H__
#define __SPRITEACTOR_H__

#include <iostream>
#include <typeinfo>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ResourceManager.hpp"

class SpriteEntity : public Entity
{
public:
    SpriteEntity(ResourceManager &rm);
    ~SpriteEntity();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    void setTexture(sf::Texture *texture);
    void setSpriteOrigin(const float &x, const float &y) { sprite_.setOrigin(x, y); }

private:
    sf::Sprite sprite_;
};

#endif // __SPRITEACTOR_H__