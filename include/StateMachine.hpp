#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>

typedef unsigned int StateId;

template <class T, class U, class V>
class StateMachine
{
public:
    StateMachine(T *target) : startState(0),
                              firstRunCurrentState(true),
                              currentState(nullptr),
                              target_(target),
                              eventCounter(0)
                              {};
    ~StateMachine(){};

    StateId addState(StateId (T::*handler)(bool, U &));

    bool setStartState(const StateId &stateid);

    bool setState(const StateId &stateid);

    void queueEvent(const V &event);

    bool polEvent(V &event);

    void resetEvent();

    void updateState(U &dataInput);

private:
    std::vector<StateId (T::*)(bool, U &)> handlers_;

    StateId startState;

    T *target_;

    bool firstRunCurrentState;

    StateId (T::*currentState)(bool, U &);

    std::vector<V> events_;
    unsigned int eventCounter;
};

template <class T, class U, class V>
StateId StateMachine<T, U, V>::addState(StateId (T::*handler)(bool, U &))
{
    handlers_.push_back(handler);

    return handlers_.size() - 1;
}

template <class T, class U, class V>
bool StateMachine<T, U, V>::setStartState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }
    startState = stateid;
    return true;
}

template <class T, class U, class V>
bool StateMachine<T, U, V>::setState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }

    StateId (T::*nextState)(bool, U &) = handlers_[stateid];

    if (nextState != currentState)
    {
        firstRunCurrentState = true;
    }

    currentState = nextState;

    return true;
}

template <class T, class U, class V>
void StateMachine<T, U, V>::queueEvent(const V &event)
{
    events_.push_back(event);
}

template<class T, class U, class V>
bool StateMachine<T, U, V>::polEvent(V &event)
{
    if (eventCounter >= events_.size()) {
        resetEvent();
        return false;
    }

    event = events_[eventCounter];
    eventCounter += 1;
    return true;
}

template<class T, class U, class V>
void StateMachine<T, U, V>::resetEvent()
{
    events_.clear();
    eventCounter = 0;
}

template <class T, class U, class V>
void StateMachine<T, U, V>::updateState(U &dataInput)
{
    if (currentState == nullptr)
    {
        if (!setState(startState))
        {
            resetEvent();
            return;
        }
    }

    StateId nextStateId = (target_->*currentState)(firstRunCurrentState, dataInput);

    if (firstRunCurrentState)
        firstRunCurrentState = false;

    setState(nextStateId);
    resetEvent();
}

#endif // __STATEMACHINE_H__