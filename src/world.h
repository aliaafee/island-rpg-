#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "actor.h"
#include "camera.h"

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
    std::vector<Actor *> _actors;

    Camera *_camera;
};

#endif // __WORLD_H__