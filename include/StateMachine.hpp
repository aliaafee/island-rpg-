#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <string>
#include <cctype>
#include <iostream>
#include <vector>

typedef unsigned int StateId;

template <class T, class U>
class StateMachine
{
public:
    StateMachine(T *target) : startState(0),
                              firstRunCurrentState(true),
                              currentState(nullptr),
                              target_(target){};
    ~StateMachine(){};

    StateId addState(StateId (T::*handler)(bool, U&));

    bool setStartState(const StateId &stateid);

    bool setState(const StateId &stateid);

    void updateState(U& dataInput);

private:
    std::vector<StateId (T::*)(bool, U&)> handlers_;
    StateId startState;

    T *target_;

    bool firstRunCurrentState;

    StateId (T::*currentState)(bool, U&);
};

template <class T, class U>
StateId StateMachine<T, U>::addState(StateId (T::*handler)(bool, U&))
{
    handlers_.push_back(handler);

    return handlers_.size() - 1;
}

template <class T, class U>
bool StateMachine<T, U>::setStartState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }
    startState = stateid;
    return true;
}

template <class T, class U>
bool StateMachine<T, U>::setState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }

    StateId (T::*nextState)(bool, U&) = handlers_[stateid];

    if (nextState != currentState)
    {
        firstRunCurrentState = true;
    }

    currentState = nextState;

    return true;
}

template <class T, class U>
void StateMachine<T, U>::updateState(U& dataInput)
{
    if (currentState == nullptr)
    {
        if (!setState(startState))
        {
            return;
        }
    }

    StateId nextStateId = (target_->*currentState)(firstRunCurrentState, dataInput);

    if (firstRunCurrentState)
        firstRunCurrentState = false;

    setState(nextStateId);
}

#endif // __STATEMACHINE_H__