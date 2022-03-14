#include "Actor.hpp"

Actor::Actor() : baseRect2_(sf::LinesStrip, 7),
                 position_(0, 0, 0)
{
    std::cout << "Creating Actor"
              << "\n";

    baseRect3_.resize(7);

    setSize(Vector3f(10, 10, 10));

    for (int i = 0; i < baseRect2_.getVertexCount(); i++)
    {
        baseRect2_[i].color.r = 0;
        baseRect2_[i].color.g = 0;
        baseRect2_[i].color.b = 0;
    }
}

Actor::Actor(ResourceManager &rm) : Actor()

{
    this->rm = &rm;
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

    Vector3f t;
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

const Vector3f &Actor::getPosition() const
{
    return position_;
}

void Actor::setPosition(const Vector3f &position)
{
    position_ = position;
}

void Actor::setPosition(const float &x, const float &y, const float &z)
{
    position_.x = x;
    position_.y = y;
    position_.z = z;
}

void Actor::move(const Vector3f &velocity)
{
    position_ += velocity;
}

void Actor::move(const float &x, const float &y, const float &z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
}

const Vector3f &Actor::getSize() const
{
    return size_;
}

void Actor::setSize(const Vector3f &size)
{
    size_ = size;
    baseRect3_[0] = Vector3f(size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[1] = Vector3f(size_.x / 2.0, -size_.y / 2.0, 0);
    baseRect3_[2] = Vector3f(-size_.x / 2.0, -size_.y / 2.0, 0);
    baseRect3_[3] = Vector3f(-size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[4] = Vector3f(size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[5] = Vector3f(0, 0, 0);
    baseRect3_[6] = Vector3f(size_.x / 2.0, -size_.y / 2.0, 0);
}

void Actor::setSize(const float &x, const float &y, const float &z)
{
    size_.x = x;
    size_.y = y;
    size_.z = z;
}

const Vector3f &Actor::getScreenPosition() const
{
    return screenPosition_;
}

Vector2f Actor::getScreenPosition2() const
{
    return Vector2f(
        screenPosition_.x,
        screenPosition_.y);
}

bool actorDepthComp(Actor *a, Actor *b)
{
    return a->getScreenPosition().z < b->getScreenPosition().z;
}
