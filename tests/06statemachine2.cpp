#include <iostream>

#include "StateMachine2.hpp"

using namespace std;

class Thing;

typedef enum ThingStateEvent
{
    WALK_TO_TARGET,
    STOP
} ThingStateEvent;
typedef StateEventQueue<ThingStateEvent> ThingEventQueue;
typedef State<Thing, int, ThingStateEvent> ThingBaseState;

class IdleState;
class WalkState;

class Thing
{
public:
    static IdleState idle;
    static WalkState walking;

    bool attackTarget;
    int data;
    StateMachine2<Thing, int, ThingStateEvent> sm;

    Thing();
    void update(sf::Time &elapsed);
    void stop();
};

class IdleState : public ThingBaseState
{
public:
    virtual void enter(Thing *target_);
    virtual ThingBaseState *update(Thing *target_,
                                   sf::Time &elapsed,
                                   int &dataInput,
                                   ThingEventQueue &events);
    virtual void exit(Thing *target_);
};

class WalkState : public ThingBaseState
{
public:
    virtual void enter(Thing *target_);
    virtual ThingBaseState *update(Thing *target_,
                                   sf::Time &elapsed,
                                   int &dataInput,
                                   ThingEventQueue &events);
    virtual void exit(Thing *target_);
};

//#########SRC

IdleState Thing::idle;
WalkState Thing::walking;

Thing::Thing() : sm(this, &(Thing::idle)), attackTarget(false)
{
    ;
}

void Thing::update(sf::Time &elapsed)
{
    data = 10;
    sm.updateState(elapsed, data);
}

void Thing::stop()
{
    sm.queueEvent(ThingStateEvent::STOP);
}

void IdleState::enter(Thing *target_)
{
    cout << "Entered idle.\n";
}

ThingBaseState *IdleState::update(Thing *target_,
                                  sf::Time &elapsed,
                                  int &dataInput,
                                  ThingEventQueue &events)
{
    cout << "Updating Idle idle.\n";
    if (target_->attackTarget)
    {
        return &(Thing::walking);
    }
    return nullptr;
}

void IdleState::exit(Thing *target_)
{
    cout << "Exiting idle.\n";
}

void WalkState::enter(Thing *target_)
{
    target_->attackTarget = false;
    cout << "Entered walk.\n";
}

ThingBaseState *WalkState::update(Thing *target_,
                                  sf::Time &elapsed,
                                  int &dataInput,
                                  ThingEventQueue &events)
{
    cout << "Updating walk walk.\n";
    ThingStateEvent event;
    while (events.pollEvent(event))
    {
        switch (event)
        {
        case ThingStateEvent::STOP:
            return &(Thing::idle);
            break;

        default:
            break;
        }
    }
    return nullptr;
}

void WalkState::exit(Thing *target_)
{
    cout << "Exiting Walk.\n";
}

//######END SRC FILE########

int main()
{
    std::cout << "# Testing Statemachine 2" << std::endl;

    Thing w;

    sf::Time time;

    w.attackTarget = false;
    w.update(time);
    w.update(time);
    w.update(time);
    w.attackTarget = true;
    w.update(time);
    w.update(time);
    w.update(time);
    w.update(time);
    w.stop();
    w.update(time);
    w.update(time);
    w.update(time);
    w.update(time);

    return 0;
}
