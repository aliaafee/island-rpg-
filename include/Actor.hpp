#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"

class World;

class Actor
{
public:
    Actor();
    Actor(ResourceManager &rm);
    ~Actor();

    virtual void update(sf::Time &elapsed, World &world);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    const Vector3f &getPosition() const;
    void setPosition(const Vector3f &position);
    void setPosition(const float &x, const float &y, const float &z);
    void move(const Vector3f &velocity);
    void move(const float &x, const float &y, const float &z);

    const Vector3f &getSize() const;
    void setSize(const Vector3f &size);
    void setSize(const float &x, const float &y, const float &z);

    const Vector3f &getScreenPosition() const;
    Vector2f getScreenPosition2() const;

protected:
    ResourceManager *rm;

private:
    Vector3f position_;
    Vector3f size_;

    Vector3f screenPosition_;

    std::vector<Vector3f> baseRect3_;
    sf::VertexArray baseRect2_;
};

bool actorDepthComp(Actor *a, Actor *b);

#endif // __ACTOR_H__