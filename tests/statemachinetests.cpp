#include "../include/StateMachine.hpp"

#include <iostream>

class Thing
{
public:
    Thing() : target(false), sm(this, "idle")
    {
        sm.addState("idle", &Thing::idleHandler);
        sm.addState("walk", &Thing::walkHandler);
    };
    ~Thing(){};

    std::string idleHandler(bool firstRun)
    {
        if (firstRun)
        {
            std::cout << "Transition -> ";
        }
        std::cout << "Idle"
                  << "\n";
        if (target)
        {
            return "walk";
        }
        return "idle";
    }

    std::string walkHandler(bool firstRun)
    {
        if (firstRun)
        {
            std::cout << "Transition -> ";
        }
        std::cout << "Walk"
                  << "\n";
        return "walk";
    }

    void update()
    {
        sm.updateState();
    }

    bool target;
    StateMachine<Thing> sm;
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