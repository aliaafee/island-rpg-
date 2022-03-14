#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <queue>
#include <vector>
#include <SFML/System.hpp>

typedef unsigned int StateId;

template <class TargetType, class DataType, class StateEventType>
class StateMachine
{
public:
    StateMachine(TargetType *target) : startState(0),
                                       firstRunCurrentState(true),
                                       currentState(nullptr),
                                       target_(target){};
    ~StateMachine(){};

    StateId addState(StateId (TargetType::*handler)(bool, sf::Time &, DataType &));

    bool setStartState(const StateId &stateid);

    bool setState(const StateId &stateid);

    void queueEvent(const StateEventType &event);

    bool pollEvent(StateEventType &event);

    void resetEvent();

    void updateState(sf::Time &elapsed, DataType &dataInput);

private:
    std::vector<StateId (TargetType::*)(bool, sf::Time &, DataType &)> handlers_;

    StateId startState;

    TargetType *target_;

    bool firstRunCurrentState;

    StateId (TargetType::*currentState)(bool, sf::Time &, DataType &);

    std::queue<StateEventType> eventQueue_;
};

template <class TargetType, class DataType, class StateEventType>
StateId StateMachine<TargetType, DataType, StateEventType>::addState(StateId (TargetType::*handler)(bool, sf::Time &, DataType &))
{
    handlers_.push_back(handler);

    return handlers_.size() - 1;
}

template <class TargetType, class DataType, class StateEventType>
bool StateMachine<TargetType, DataType, StateEventType>::setStartState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }
    startState = stateid;
    return true;
}

template <class TargetType, class DataType, class StateEventType>
bool StateMachine<TargetType, DataType, StateEventType>::setState(const StateId &stateid)
{
    if (stateid > handlers_.size() - 1)
    {
        return false;
    }

    StateId (TargetType::*nextState)(bool, sf::Time &, DataType &) = handlers_[stateid];

    if (nextState != currentState)
    {
        firstRunCurrentState = true;
    }

    currentState = nextState;

    return true;
}

template <class TargetType, class DataType, class StateEventType>
void StateMachine<TargetType, DataType, StateEventType>::queueEvent(const StateEventType &event)
{
    eventQueue_.push(event);
}

template <class TargetType, class DataType, class StateEventType>
bool StateMachine<TargetType, DataType, StateEventType>::pollEvent(StateEventType &event)
{
    if (eventQueue_.empty())
    {
        return false;
    }

    event = eventQueue_.front();
    eventQueue_.pop();

    return true;
}

template <class TargetType, class DataType, class StateEventType>
void StateMachine<TargetType, DataType, StateEventType>::resetEvent()
{
    std::queue<StateEventType> empty;
    std::swap(eventQueue_, empty);
}

template <class TargetType, class DataType, class StateEventType>
void StateMachine<TargetType, DataType, StateEventType>::updateState(sf::Time &elapsed, DataType &dataInput)
{
    if (currentState == nullptr)
    {
        if (!setState(startState))
        {
            resetEvent();
            return;
        }
    }

    StateId nextStateId = (target_->*currentState)(firstRunCurrentState, elapsed, dataInput);

    if (firstRunCurrentState)
        firstRunCurrentState = false;

    setState(nextStateId);
    resetEvent();
}

#endif // __STATEMACHINE_H__