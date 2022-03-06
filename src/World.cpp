#include "World.h"

World::World(int64_t width, int64_t height)
{
    std::cout << "Creating World"
              << "\n";

    camera_ = new Camera(
        sf::Vector3f(0, 0, 0),
        sf::Vector3f(800 / 2, 600 / 2, 0),
        sf::Vector2f(64, 32),
        10);

    addActor(new SpriteActor());

    addActor(new Actor());

    //actors_[0]->setPosition(sf::Vector3f(0, 0, 0));
    //actors_[1]->setPosition(sf::Vector3f(0, 30, 10));
    
    Actor* a;
    for (float i; i < 1; i++) {
        a = new SpriteActor();
        a->setPosition(sf::Vector3f(i*6, 0, 0));
        addActor(a);
    }
}

World::~World()
{
    std::cout << "Destroying World"
              << "\n";

    delete camera_;

    for (auto &actor : actors_)
    {
        delete actor;
    }
    actors_.clear();
}

void World::update()
{
    for (auto &actor : actors_)
    {
        actor->update(*this);
    }
}

void World::transform()
{
    for (auto &actor : actors_)
    {
        actor->transform(*camera_);
    }
}

void World::draw(sf::RenderTarget *screen)
{
    std::stable_sort(actors_.begin(), actors_.end(), actorDepthComp);

    for (auto &actor : actors_)
    {
        actor->draw(screen);
    }
}

void World::addActor(Actor *actor)
{
    actors_.push_back(actor);
}