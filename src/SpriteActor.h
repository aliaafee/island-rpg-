#ifndef __SPRITEACTOR_H__
#define __SPRITEACTOR_H__

#include <iostream>
#include <typeinfo>
#include <SFML/Graphics.hpp>

#include "Actor.h"
#include "ResourceManager.h"

class SpriteActor : public Actor
{
public:
    SpriteActor(ResourceManager *rm);
    ~SpriteActor();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    void setTexture(sf::Texture *texture);

private:
    sf::Sprite sprite_;
};

#endif // __SPRITEACTOR_H__