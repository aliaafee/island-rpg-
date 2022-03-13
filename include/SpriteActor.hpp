#ifndef __SPRITEACTOR_H__
#define __SPRITEACTOR_H__

#include <iostream>
#include <typeinfo>
#include <SFML/Graphics.hpp>

#include "Actor.hpp"
#include "ResourceManager.hpp"

class SpriteActor : public Actor
{
public:
    SpriteActor(ResourceManager &rm);
    ~SpriteActor();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    void setTexture(sf::Texture *texture);
    void setSpriteOrigin(const float &x, const float &y) { sprite_.setOrigin(x, y); }

private:
    sf::Sprite sprite_;
};

#endif // __SPRITEACTOR_H__