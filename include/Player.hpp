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

    void walkTo(const sf::Vector3f &target);
    void stop();
private:
    enum StateEvent {
        WALK_TO_TARGET,
        STOP
    };

    StateMachine<Player, World, StateEvent> statemachine_;

    StateId idleStateId;
    StateId walkStateId;

    StateId idleState(bool firstRun, World &world);
    StateId walkState(bool firstRun, World &world);

    int testCounter;
};

#endif // __PLAYER_H__