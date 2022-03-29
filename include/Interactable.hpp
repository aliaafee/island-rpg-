#ifndef __INTERACTABLE_H__
#define __INTERACTABLE_H__

#include "AnimatedEntity.hpp"
#include "StateMachine2.hpp"
//#include "Player.hpp"
#include "World.hpp"

DEFINE_STATE_EVENTS(FirePit,
                    FIREPIT_ATTACK);

class FirePitOn;
class FirePitOff;

class FirePit : public Entity
{
public:
    FirePit(ResourceManager &rm);
    ~FirePit(){};

    virtual void update(sf::Time &elapsed, World &world);
    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    virtual void attack(); // World &world, Player &player);

private:
    STATE_MACHINE(FirePit, World)
    statemachine_;

    STATE_INSTANCE(FirePitOn);
    STATE_INSTANCE(FirePitOff);

    sf::CircleShape fire_;
    float intensity_;
};

DECLARE_STATE_CLASS(FirePit, World);

class FirePitOn : public STATE_CLASS(FirePit)
{
public:
    STATE_ENTER(FirePit, World);
    STATE_UPDATE(FirePit, World);
};

class FirePitOff : public STATE_CLASS(FirePit)
{
public:
    STATE_ENTER(FirePit, World);
    STATE_UPDATE(FirePit, World);
};

#endif // __INTERACTABLE_H__