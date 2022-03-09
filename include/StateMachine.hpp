#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <string>
#include <cctype>
#include <iostream>
#include <vector>

typedef unsigned int StateId;

template <class T>
class StateMachine
{
public:
    StateMachine(T *target) : startState(0),
                              firstRunCurrentState(true),
                              currentState(nullptr),
                              target_(target){};
    ~StateMachine(){};

    StateId addState(StateId (T::*handler)(bool));

    bool setStartState(const StateId &stateid);

    bool setState(const StateId &stateid);

    void updateState();

private:
    std::vector<StateId (T::*)(bool)> handlers_;
    StateId startState;

    T *target_;

    bool firstRunCurrentState;

    StateId (T::*currentState)(bool);
};

template <class T>
StateId StateMachine<T>::addState(StateId (T::*handler)(bool))
{
    handlers_.push_back(handler);

    return handlers_.size() - 1;
}

template <class T>
bool StateMachine<T>::setStartState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }
    startState = stateid;
    return true;
}

template <class T>
bool StateMachine<T>::setState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }

    StateId (T::*nextState)(bool) = handlers_[stateid];

    if (nextState != currentState)
    {
        firstRunCurrentState = true;
    }

    currentState = nextState;

    return true;
}

template <class T>
void StateMachine<T>::updateState()
{
    if (currentState == nullptr)
    {
        if (!setState(startState))
        {
            return;
        }
    }

    StateId nextStateId = (target_->*currentState)(firstRunCurrentState);

    if (firstRunCurrentState)
        firstRunCurrentState = false;

    setState(nextStateId);
}

#endif // __STATEMACHINE_H__