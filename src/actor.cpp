#include "actor.h"

Actor::Actor()
{
    std::cout << "Creating Actor"
              << "\n";
    _circle = new sf::CircleShape(10.0f);
    _circle->setPointCount(10);
    _circle->setOutlineColor(sf::Color::Green);
    _circle->setOutlineThickness(2);
}

Actor::~Actor()
{
    std::cout << "Destroying Actor"
              << "\n";
    delete _circle;
}

void Actor::update()
{
    _position.z += 0.5;
}

void Actor::update(std::vector<Actor *> &other_actors)
{
    update();
    // for (auto &actor : other_actors)
    // {
    //     if (actor != this)
    //     {
    //         ;
    //     }
    // }
}

void Actor::update(World &world)
{
    ;
}

void Actor::transform(Camera &camera)
{
    sf::Vector3 scree_pos = camera.transform(_position);
    _circle->setPosition(sf::Vector2f(scree_pos.x, scree_pos.y));
}

void Actor::draw(sf::RenderTarget *screen)
{
    screen->draw(*_circle);
}

const sf::Vector3f &Actor::getPosition() const
{
    return _position;
}

void Actor::setPosition(const sf::Vector3f &position)
{
    _position = position;
}

bool actorDepthComp(Actor* a, Actor* b)
{
    return a->getPosition().z < b->getPosition().z;
}
