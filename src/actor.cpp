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
    incPosition(sf::Vector3f(1, 0, 0));
}

void Actor::update(std::vector<Actor *> &other_actors)
{
    update();
}

void Actor::update(World &world)
{
    update();
}

void Actor::transform(Camera &camera)
{
    sf::Vector3 screenPos = camera.transform(_position);
    _circle->setPosition(sf::Vector2f(screenPos.x, screenPos.y));
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

void Actor::incPosition(const sf::Vector3f &velocity)
{
    _position += velocity; 
}

bool actorDepthComp(Actor* a, Actor* b)
{
    return a->getPosition().z < b->getPosition().z;
}
