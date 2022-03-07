#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "ResourceManager.h"

class World;

class Actor
{
public:
    Actor(ResourceManager* rm);
    ~Actor();

    virtual void update(sf::Time &elapsed, World &world);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    const sf::Vector3f &getPosition() const;
    void setPosition(const sf::Vector3f &position);
    void setPosition(const float &x, const float &y, const float &z);
    void move(const sf::Vector3f &velocity);
    void move(const float &x, const float &y, const float &z);

    const sf::Vector3f &getSize() const;
    void setSize(const sf::Vector3f &size);
    void setSize(const float &x, const float &y, const float &z);

    const sf::Vector3f &getScreenPosition() const;
private:
    sf::Vector3f position_;
    sf::Vector3f size_;

    sf::Vector3f screenPosition_;

    std::vector<sf::Vector3f> baseRect3_;
    sf::VertexArray baseRect2_;
};

bool actorDepthComp(Actor* a, Actor* b);


#endif // __ACTOR_H__