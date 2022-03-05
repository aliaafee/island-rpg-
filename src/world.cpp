#include "world.h"

World::World(int64_t width, int64_t height)
{
    std::cout << "Creating World"
              << "\n";
    addActor(new Actor());

    addActor(new Actor());

    _actors[0]->setPosition(sf::Vector3f(0, 0, 0));
    _actors[1]->setPosition(sf::Vector3f(0, 30, 10));
}

World::~World()
{
    std::cout << "Destroying World"
              << "\n";
    for (auto & actor : _actors)
    {
        delete actor;
    }
    _actors.clear();
}

void World::update()
{
    for (auto & actor : _actors)
    {
        actor->update(_actors);
    }
}

void World::transform()
{
    for (auto & actor : _actors)
    {
        actor->transform();
    }
}

void World::draw(sf::RenderTarget *screen)
{
    std::sort(_actors.begin(), _actors.end(), actorDepthComp);

    for (auto & actor : _actors)
    {
        actor->draw(screen);
    }
}

void World::addActor(Actor* actor)
{
    _actors.push_back(actor);
}