#include "Actor.h"

Actor::Actor(ResourceManager* rm) : baseRect2_(sf::LinesStrip, 7), position_(0, 0, 0), size_(10.0, 10.0, 10.0)
{
    std::cout << "Creating Actor"
              << "\n";

    baseRect3_.push_back(sf::Vector3f(size_.x / 2.0, size_.y / 2.0, 0));
    baseRect3_.push_back(sf::Vector3f(size_.x / 2.0, -size_.y / 2.0, 0));
    baseRect3_.push_back(sf::Vector3f(-size_.x / 2.0, -size_.y / 2.0, 0));
    baseRect3_.push_back(sf::Vector3f(-size_.x / 2.0, size_.y / 2.0, 0));
    baseRect3_.push_back(sf::Vector3f(size_.x / 2.0, size_.y / 2.0, 0));
    baseRect3_.push_back(sf::Vector3f(0, 0, 0));
    baseRect3_.push_back(sf::Vector3f(size_.x / 2.0, -size_.y / 2.0, 0));

    for (int i = 0; i < baseRect2_.getVertexCount(); i++)
    {
        baseRect2_[i].color.r = 0;
        baseRect2_[i].color.g = 0;
        baseRect2_[i].color.b = 0;
    }
}

Actor::~Actor()
{
    std::cout << "Destroying Actor"
              << "\n";
}

void Actor::update(sf::Time &elapsed, World &world)
{
    ;
}

void Actor::transform(Camera &camera)
{
    screenPosition_ = camera.transform(position_);

    sf::Vector3f t;
    for (int i = 0; i < baseRect3_.size(); ++i)
    {
        t = camera.transform(baseRect3_[i] + position_);
        baseRect2_[i].position.x = t.x;
        baseRect2_[i].position.y = t.y;
    }
}

void Actor::draw(sf::RenderTarget *screen)
{
    screen->draw(baseRect2_);
}

const sf::Vector3f &Actor::getPosition() const
{
    return position_;
}

void Actor::setPosition(const sf::Vector3f &position)
{
    position_ = position;
}

void Actor::setPosition(const float &x, const float &y, const float &z)
{
    position_.x = x;
    position_.y = y;
    position_.z = z;
}

void Actor::move(const sf::Vector3f &velocity)
{
    position_ += velocity;
}

void Actor::move(const float &x, const float &y, const float &z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
}

const sf::Vector3f& Actor::getSize() const
{
    return size_;
}

void Actor::setSize(const sf::Vector3f &size)
{
    size_ = size;
}

void Actor::setSize(const float &x, const float &y, const float &z)
{
    size_.x = x;
    size_.y = y;
    size_.z = z;
}

const sf::Vector3f &Actor::getScreenPosition() const
{
    return screenPosition_;
}

bool actorDepthComp(Actor *a, Actor *b)
{
    return a->getScreenPosition().z < b->getScreenPosition().z;
}
