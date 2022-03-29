#include "Entity.hpp"

Entity::Entity() : baseRect2_(sf::LinesStrip, 7),
                   position_(0, 0, 0)
{
    // std::cout << "Creating Entity"
    //           << "\n";

    baseRect3_.resize(7);

    setSize(Vector3f(10, 10, 10));

    for (int i = 0; i < baseRect2_.getVertexCount(); i++)
    {
        baseRect2_[i].color.r = 0;
        baseRect2_[i].color.g = 0;
        baseRect2_[i].color.b = 0;
    }
}

Entity::Entity(ResourceManager &rm) : Entity()

{
    this->rm = &rm;
}

Entity::~Entity()
{
    // std::cout << "Destroying Entity"
    //           << "\n";
    ;
}

void Entity::update(sf::Time &elapsed, World &world)
{
    ;
}

void Entity::transform(Camera &camera)
{
    screenPosition_ = camera.transform(getPosition());

    Vector3f t;
    for (int i = 0; i < baseRect3_.size(); ++i)
    {
        t = camera.transform(baseRect3_[i] + getPosition());
        baseRect2_[i].position.x = t.x;
        baseRect2_[i].position.y = t.y;
    }
}

void Entity::draw(sf::RenderTarget *screen)
{
    screen->draw(baseRect2_);
}

Vector3f Entity::getPosition() const
{
    return origin_ + position_;
}

const Vector3f &Entity::getLocalPosition() const
{
    return position_;
}

void Entity::setLocalPosition(const Vector3f &position)
{
    position_ = position;
}

void Entity::translateOrigin(const Vector3f &newOrigin)
{
    // position_ += origin_ - newOrigin;
    position_ = translateOrigin(origin_, newOrigin, position_);
    origin_ = newOrigin;
}

const Vector3f &Entity::getOrigin() const
{
    return origin_;
}

Vector3f Entity::translateOrigin(const Vector3f &oldOrigin, const Vector3f &newOrigin, const Vector3f point) const
{
    return point + oldOrigin - newOrigin;
}

Vector3f Entity::toLocal(const Vector3f &globalPoint)
{
    return globalPoint - origin_;
}

void Entity::setPosition(const Vector3f &position)
{
    position_ = position - origin_;
}

void Entity::setPosition(const float &x, const float &y, const float &z)
{
    position_.x = x - origin_.x;
    position_.y = y - origin_.y;
    position_.z = z - origin_.z;
}

void Entity::move(const Vector3f &velocity)
{
    position_ += velocity;
}

void Entity::move(const float &x, const float &y, const float &z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
}

const Vector3f &Entity::getSize() const
{
    return size_;
}

void Entity::setSize(const Vector3f &size)
{
    setSize(size.z, size.y, size.z);
}

void Entity::setSize(const float &x, const float &y, const float &z)
{
    size_.x = x;
    size_.y = y;
    size_.z = z;

    sizeRadius_ = sqrt((size_.x / 2.f) * (size_.x / 2.f) + (size_.y / 2.f) * (size_.y / 2.f));

    baseRect3_[0] = Vector3f(size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[1] = Vector3f(size_.x / 2.0, -size_.y / 2.0, 0);
    baseRect3_[2] = Vector3f(-size_.x / 2.0, -size_.y / 2.0, 0);
    baseRect3_[3] = Vector3f(-size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[4] = Vector3f(size_.x / 2.0, size_.y / 2.0, 0);
    baseRect3_[5] = Vector3f(0, 0, 0);
    baseRect3_[6] = Vector3f(size_.x / 2.0, -size_.y / 2.0, 0);
}

const float &Entity::getSizeRadius() const
{
    return sizeRadius_;
}

const Vector3f &Entity::getScreenPosition() const
{
    return screenPosition_;
}

Vector2f Entity::getScreenPosition2() const
{
    return Vector2f(
        screenPosition_.x,
        screenPosition_.y);
}

bool Entity::collision(const Entity &other)
{
    Vector3f origin = getPosition() - (getSize() / 2.f);
    Vector3f otherOrigin = other.getPosition() - (other.getSize() / 2.f);

    if ((origin.x < otherOrigin.x + other.getSize().x) &&
        (origin.x + getSize().x > otherOrigin.x) &&
        (origin.y < otherOrigin.y + other.getSize().y) &&
        (getSize().y + origin.y > otherOrigin.y))
    {
        return true;
    }

    return false;
}

bool entityDepthComp(Entity *a, Entity *b)
{
    return a->getScreenPosition().z < b->getScreenPosition().z;
}
