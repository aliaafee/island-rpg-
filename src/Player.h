#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "AnimatedActor.h"
#include "ResourceManager.h"
#include "World.h"

class Player : public AnimatedActor
{
public:
    Player(ResourceManager *rm);
    ~Player();

    virtual void update(sf::Time &elapsed, World &world);
};

#endif // __PLAYER_H__