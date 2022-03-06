#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Actor.h"
#include "Camera.h"
#include "SpriteActor.h"

class World
{
public:
    World(int64_t width, int64_t height);
    ~World();

    void update();
    void transform();
    void draw(sf::RenderTarget *screen);

    void addActor(Actor *actor);

private:
    std::vector<Actor *> actors_;

    Camera *camera_;
};

#endif // __WORLD_H__