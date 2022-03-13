#ifndef __WORLD_H__
#define __WORLD_H__

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Vector.hpp"
#include "Pathfinder.hpp"
#include "Actor.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"

class Player;

class World
{
public:
    World(sf::RenderWindow &window, ResourceManager &rm, int64_t width, int64_t height);
    ~World();

    void update(sf::Time &elapsed);
    void transform();
    void draw(sf::RenderTarget *screen);

    void addActor(Actor *actor);
    const std::vector<Actor *> &getActors() const;

    void onMouseButtonReleased(const sf::Event &event);
    void onMouseWheelScrolled(const sf::Event &event);

    bool findPath(const Vector3f &start, const Vector3f &end,
                  const bool &diagonal,
                  std::deque<Vector3f> &resultPath)
    {
        return pathfinder_.findPath(start, end, diagonal, resultPath);
    }

private:
    Player *player_;
    Actor *cursor_;
    std::vector<Actor *> actors_;

    Camera camera_;
    ResourceManager *rm_;
    sf::RenderWindow *window_;

    Pathfinder pathfinder_;

    void input_(sf::Time &elapsed);
};

#endif // __WORLD_H__