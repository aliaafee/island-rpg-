#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "actor.h"

class World
{
public:
    World(int64_t width, int64_t height);
    ~World();

    void update();
    void transform();
    void draw(sf::RenderTarget *screen);

    void addActor(Actor* actor);


private:
    std::vector<Actor*> _actors;
};

#endif // __WORLD_H__