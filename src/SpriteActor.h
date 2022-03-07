#ifndef __SPRITEACTOR_H__
#define __SPRITEACTOR_H__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Actor.h"
#include "World.h"

class SpriteActor : public Actor
{
public:
    SpriteActor(ResourceManager* rm);
    ~SpriteActor();

    virtual void update(World &world);
    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);
private:
    sf::Sprite sprite_;
};

#endif // __SPRITEACTOR_H__