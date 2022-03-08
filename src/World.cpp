#include "World.h"

World::World(ResourceManager *rm,
             int64_t width, int64_t height) : rm_(rm),
                                              player_(new Player(rm))
{
    std::cout << "Creating World"
              << "\n";

    camera_ = new Camera(
        sf::Vector3f(0, 0, 0),
        sf::Vector3f(800 / 2, 600 / 2, 0),
        sf::Vector2f(64, 32),
        10);

    addActor(player_);

    // addActor(new Player(rm_));

    // addActor(new Player(rm_));

    // actors_[0]->setPosition(sf::Vector3f(0, 20, 0));
    // // actors_[1]->setPosition(sf::Vector3f(0, 30, 10));

    // Actor *a;
    // for (float i; i < 10; i++)
    // {
    //     a = new Player(rm_);
    //     a->setPosition(sf::Vector3f(20 + i * 6, 0, 0));
    //     addActor(a);
    // }
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

void World::update(sf::Time &elapsed)
{
    for (auto &actor : actors_)
    {
        actor->update(elapsed, *this);
    }

    float speed = elapsed.asSeconds() * 4.0 * 60;
    sf::Vector2f panDir(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        panDir.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        panDir.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        panDir.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        panDir.y = speed;
    }
    if (abs(panDir.x) > 0 || abs(panDir.y) > 0)
    {
        camera_->pan(panDir);
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

const std::vector<Actor *> &World::getActors() const
{
    return actors_;
}