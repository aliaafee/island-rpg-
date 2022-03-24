#ifndef __STATEMACHINE2_H__
#define __STATEMACHINE2_H__

#include <SFML/System.hpp>
#include <queue>

template <class StateEvent>
class StateEventQueue
{
private:
    std::queue<StateEvent> eventQueue_;

public:
    void queueEvent(const StateEvent &event)
    {
        eventQueue_.push(event);
    }
    bool pollEvent(StateEvent &event)
    {
        if (eventQueue_.empty())
            return false;
        event = eventQueue_.front();
        eventQueue_.pop();
        return true;
    }
    void reset()
    {
        std::queue<StateEvent> empty;
        std::swap(eventQueue_, empty);
    }
};

template <class Target, class Data, typename StateEvent>
class State
{
public:
    State(){};
    virtual void enter(Target *target_, Data &dataInput){};
    virtual State<Target, Data, StateEvent>
        *update(Target *target_,
                sf::Time &elapsed,
                Data &dataInput,
                StateEventQueue<StateEvent> &events) { return nullptr; }
    virtual void exit(Target *target_, Data &dataInput){};
};

template <class Target, class Data, typename StateEvent>
class StateMachine2
{
private:
    Target *target_;
    State<Target, Data, StateEvent> *startState_;
    State<Target, Data, StateEvent> *currentState_;
    StateEventQueue<StateEvent> events_;

public:
    StateMachine2(Target *target,
                  State<Target, Data, StateEvent> *startState) : target_(target),
                                                                 startState_(startState),
                                                                 currentState_(nullptr) { ; }

    State<Target, Data, StateEvent> *getCurrentState(Data &dataInput)
    {
        if (currentState_ == nullptr)
        {
            currentState_ = startState_;
            currentState_->enter(target_, dataInput);
        }
        return currentState_;
    }

    void updateState(State<Target, Data, StateEvent> *nextState, Data &dataInput)
    {
        if (nextState != nullptr)
        {
            currentState_->exit(target_, dataInput);
            currentState_ = nextState;
            currentState_->enter(target_, dataInput);
        }
    }

    void updateState(sf::Time &elapsed, Data &dataInput)
    {
        updateState(
            getCurrentState(dataInput)->update(target_,
                                               elapsed,
                                               dataInput,
                                               events_),
            dataInput);

        events_.reset();
    }

    void queueEvent(const StateEvent &event)
    {
        events_.queueEvent(event);
    }
};

#define DEFINE_STATE_EVENTS(TARGETCLASS, ...) \
    typedef enum TARGETCLASS##Event{          \
        __VA_ARGS__} TARGETCLASS##Event;      \
    typedef StateEventQueue<TARGETCLASS##Event> TARGETCLASS##EventQueue;

#define DECLARE_STATE_CLASS(TARGETCLASS, DATACLASS) \
    typedef State<TARGETCLASS, DATACLASS, TARGETCLASS##Event> TARGETCLASS##State;

#define STATE_MACHINE(TARGETCLASS, DATACLASS) \
    StateMachine2<TARGETCLASS, DATACLASS, TARGETCLASS##Event>

#define STATE_CLASS(TARGETCLASS) \
    TARGETCLASS##State

#define EVENT_QUEUE(TARGETCLASS) \
    TARGETCLASS##EventQueue

#define STATE_INSTANCE(NAME)    \
    static NAME NAME##Instance; \
    friend class NAME

#define STATE_INSTANCE_INIT(TARGETCLASS, NAME) \
    NAME TARGETCLASS::NAME##Instance;

#define STATE(TARGETCLASS, NAME) \
    &(TARGETCLASS::NAME##Instance)

#define STATE_UPDATE(TARGETCLASS, DATACLASS)                     \
    virtual STATE_CLASS(TARGETCLASS) * update(TARGETCLASS *t,    \
                                              sf::Time &elapsed, \
                                              DATACLASS &data,   \
                                              EVENT_QUEUE(TARGETCLASS) & events)

#define STATE_UPDATE_FUNCTION(TARGETCLASS, STATECLASS, DATACLASS, DATANAME) \
    STATE_CLASS(TARGETCLASS) * STATECLASS::update(TARGETCLASS *t,           \
                                                  sf::Time &elapsed,        \
                                                  DATACLASS &DATANAME,      \
                                                  EVENT_QUEUE(TARGETCLASS) & events)

#define STATE_ENTER(TARGETCLASS, DATACLASS) \
    virtual void enter(TARGETCLASS *t, DATACLASS &data)

#define STATE_ENTER_FUNCTION(TARGETCLASS, STATECLASS, DATACLASS, DATANAME) \
    void STATECLASS::enter(TARGETCLASS *t, DATACLASS &DATANAME)

#define STATE_EXIT(TARGETCLASS, DATACLASS) \
    virtual void exit(TARGETCLASS *t, DATACLASS &data)

#define STATE_EXIT_FUNCTION(TARGETCLASS, STATECLASS, DATACLASS, DATANAME) \
    void STATECLASS::exit(TARGETCLASS *t, DATACLASS &DATANAME)

#define POLL_STATE_EVENTS(TARGETCLASS) \
    TARGETCLASS##Event event;          \
    while (events.pollEvent(event))

#define CALL_STATE_UPDATE(STATECLASS, DATANAME) \
    STATECLASS::update(t, elapsed, DATANAME, events);

#define CALL_STATE_ENTER(STATECLASS, DATANAME) \
    STATECLASS::enter(t, DATANAME);

#define CALL_STATE_EXIT(STATECLASS, DATANAME) \
    STATECLASS::exit(t, DATANAME);

#endif // __STATEMACHINE2_H__
