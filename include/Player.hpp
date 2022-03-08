#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "AnimatedActor.hpp"
#include "ResourceManager.hpp"
#include "StateMachine.hpp"
#include "World.hpp"

class Player : public AnimatedActor
{
public:
    Player(ResourceManager *rm);
    ~Player();

    virtual void update(sf::Time &elapsed, World &world);

    std::string idleState(bool firstRun);
    std::string walkState(bool firstRun);

private:
    StateMachine<Player> statemachine_;

    int idleCT;
};

#endif // __PLAYER_H__