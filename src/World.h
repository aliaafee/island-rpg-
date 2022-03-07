#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Actor.h"
#include "Camera.h"
#include "SpriteActor.h"
#include "ResourceManager.h"

class World
{
public:
    World(ResourceManager *rm,int64_t width, int64_t height);
    ~World();

    void update(sf::Time &elapsed);
    void transform();
    void draw(sf::RenderTarget *screen);

    void addActor(Actor *actor);

private:
    std::vector<Actor *> actors_;

    Camera *camera_;
    ResourceManager *rm_;
};

#endif // __WORLD_H__