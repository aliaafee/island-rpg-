#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <queue>
#include <vector>

typedef unsigned int StateId;

template <class T, class U, class V>
class StateMachine
{
public:
    StateMachine(T *target) : startState(0),
                              firstRunCurrentState(true),
                              currentState(nullptr),
                              target_(target){};
    ~StateMachine(){};

    StateId addState(StateId (T::*handler)(bool, U &));

    bool setStartState(const StateId &stateid);

    bool setState(const StateId &stateid);

    void queueEvent(const V &event);

    bool pollEvent(V &event);

    void resetEvent();

    void updateState(U &dataInput);

private:
    std::vector<StateId (T::*)(bool, U &)> handlers_;

    StateId startState;

    T *target_;

    bool firstRunCurrentState;

    StateId (T::*currentState)(bool, U &);

    std::queue<V> eventQueue_;
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
    eventQueue_.push(event);
}

template <class T, class U, class V>
bool StateMachine<T, U, V>::pollEvent(V &event)
{
    if (eventQueue_.empty())
    {
        return false;
    }

    event = eventQueue_.front();
    eventQueue_.pop();

    return true;
}

template <class T, class U, class V>
void StateMachine<T, U, V>::resetEvent()
{
    std::queue<V> empty;
    std::swap(eventQueue_, empty);
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