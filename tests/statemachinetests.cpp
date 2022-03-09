#include "../include/StateMachine.hpp"

#include <iostream>

class Thing
{
public:

    StateId idleStateId;
    StateId walkStateId;

    Thing() : target(false), sm(this)
    {
        idleStateId = sm.addState(&Thing::idleHandler);
        walkStateId = sm.addState(&Thing::walkHandler);
    };
    ~Thing(){};

    StateId idleHandler(bool firstRun, int& data)
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

    StateId walkHandler(bool firstRun, int& data)
    {
        if (firstRun)
        {
            std::cout << "Transition -> ";
        }
        std::cout << "Walk data is" << data
                  << "\n";
        return walkStateId;
    }

    void update()
    {
        data = 10;
        sm.updateState(data);
    }

    bool target;
    int data;
    StateMachine<Thing, int> sm;
};

int main()
{
    std::cout << "# Testing StateMachine" << std::endl;

    Thing w;

    w.target = false;
    w.update();
    w.update();
    w.update();
    w.target = true;
    w.update();
    w.update();
    w.update();
    w.update();

    return 0;
}