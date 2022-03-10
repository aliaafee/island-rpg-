#include "../include/StateMachine.hpp"

#include <iostream>
#include <set>

class Thing
{
public:

    StateId idleStateId;
    StateId walkStateId;

    enum StateEvent {
        WALK_TO_TARGET,
        STOP
    };

    bool target;
    int data;
    StateMachine<Thing, int, StateEvent> sm;

    Thing() : target(false), sm(this)
    {
        idleStateId = sm.addState(&Thing::idleHandler);
        walkStateId = sm.addState(&Thing::walkHandler);
    };
    ~Thing(){};

    StateId idleHandler(bool firstRun, sf::Time &elapsed, int& data)
    {
        if (firstRun)
        {
            std::cout << "Transition -> ";
        }
        std::cout << "Idle" << data
                  << "\n";
        if (target)
        {
            return walkStateId;
        }
        return idleStateId;
    }

    StateId walkHandler(bool firstRun, sf::Time &elapsed, int& data)
    {
        if (firstRun)
        {
            std::cout << "Transition -> ";
        }
        std::cout << "Walk data is " << data
                  << "\n";
        return walkStateId;
    }

    void update(sf::Time &elapsed)
    {
        data = 10;
        sm.updateState(elapsed, data);
    }
};

int main()
{
    std::cout << "# Testing StateMachine" << std::endl;

    Thing w;

    sf::Time time;

    w.target = false;
    w.update(time);
    w.update(time);
    w.update(time);
    w.target = true;
    w.update(time);
    w.update(time);
    w.update(time);
    w.update(time);

    std::set<int>::iterator i;

    return 0;
}