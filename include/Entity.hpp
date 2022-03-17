#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"

class World;

class Entity
{
public:
    Entity();
    Entity(ResourceManager &rm);
    ~Entity();

    virtual void update(sf::Time &elapsed, World &world);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    Vector3f getPosition() const;

    virtual void setPosition(const Vector3f &position);
    void setPosition(const float &x, const float &y, const float &z);
    void move(const Vector3f &velocity);
    void move(const float &x, const float &y, const float &z);

    const Vector3f &getLocalPosition() const;
    void setLocalPosition(const Vector3f &position);
    void setLocalOrigin(const Vector3f &newOrigin);
    const Vector3f &getOrigin() const;
    Vector3f setOriginForPoint(const Vector3f &oldOrigin, const Vector3f &newOrigin, const Vector3f point) const;

    Vector3f toLocal(const Vector3f &globalPoint);

    const Vector3f &getSize() const;
    void setSize(const Vector3f &size);
    void setSize(const float &x, const float &y, const float &z);

    const Vector3f &getScreenPosition() const;
    Vector2f getScreenPosition2() const;

protected:
    ResourceManager *rm;

private:
    Vector3f origin_;
    Vector3f position_; // Position is relative to the origin
    Vector3f size_;

    Vector3f screenPosition_;

    std::vector<Vector3f> baseRect3_;
    sf::VertexArray baseRect2_;
};

bool entityDepthComp(Entity *a, Entity *b);

#endif // __ENTITY_H__