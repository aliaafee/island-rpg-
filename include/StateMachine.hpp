#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <string>
#include <cctype>
#include <iostream>
#include <map>

template <class T>
class StateMachine
{
public:
    StateMachine(T *target, const std::string &start);
    ~StateMachine();

    void addState(const std::string &name, std::string (T::*handler)(bool));

    bool setState(const std::string &name);

    void updateState();

private:
    std::map<const std::string, std::string (T::*)(bool)> handlers_;
    std::string startState;

    T *target_;

    bool firstRunCurrentState;
    // StateHandler currentState;

    std::string (T::*currentState)(bool);
};

template <class T>
StateMachine<T>::StateMachine(T *target, const std::string &start) : startState(start),
                                                                     firstRunCurrentState(true),
                                                                     currentState(nullptr),
                                                                     target_(target)
{
}

template <class T>
StateMachine<T>::~StateMachine()
{
}

template <class T>
void StateMachine<T>::addState(const std::string &name, std::string (T::*handler)(bool))
{
    handlers_.insert(std::pair(name, handler));
}

template <class T>
bool StateMachine<T>::setState(const std::string &name)
{
    auto nextState = handlers_.find(name);

    if (nextState == handlers_.end())
    {
        return false;
    }

    if (nextState->second != currentState)
    {
        firstRunCurrentState = true;
    }

    currentState = nextState->second;

    return true;
}

template <class T>
void StateMachine<T>::updateState()
{
    if (currentState == nullptr)
    {
        setState(startState);
    }

    std::string nextState;
    if (firstRunCurrentState)
    {
        firstRunCurrentState = false;
        nextState = (target_->*currentState)(true);
    }
    else
    {
        nextState = (target_->*currentState)(false);
    }

    setState(nextState);
}

#endif // __STATEMACHINE_H__