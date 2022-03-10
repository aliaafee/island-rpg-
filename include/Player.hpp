#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "AnimatedActor.hpp"
#include "ResourceManager.hpp"
#include "StateMachine.hpp"
#include "World.hpp"
#include "support.hpp"

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

    StateId idleState(bool firstRun, sf::Time &elapsed, World &world);

    sf::Vector3f walkTarget_;
    StateId walkState(bool firstRun, sf::Time &elapsed, World &world);

    std::string animationDirection_;
    std::string animationAction_;

    void setAnimationDirection(const std::string &direction);
    void setAnimationDirection(const sf::Vector3f &direction);
    void setAnimationAction(const std::string &action);
};

#endif // __PLAYER_H__