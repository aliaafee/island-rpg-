#include "Interactable.hpp"

STATE_INSTANCE_INIT(FirePit, FirePitOn);
STATE_INSTANCE_INIT(FirePit, FirePitOff);

FirePit::FirePit(ResourceManager &rm) : Entity(rm),
                                        statemachine_(
                                            this,
                                            STATE(FirePit, FirePitOn)),
                                        fire_(20),
                                        intensity_(0.f)
{
    fire_.setFillColor(sf::Color::Black);
}

void FirePit::update(sf::Time &elapsed, World &world)
{
    statemachine_.updateState(elapsed, world);
}

void FirePit::transform(Camera &camera)
{
    Entity::transform(camera);
    fire_.setPosition(getScreenPosition2() - Vector2f(20, 40));
}

void FirePit::draw(sf::RenderTarget *screen)
{
    Entity::draw(screen);
    screen->draw(fire_);
}

void FirePit::attack() // World &world, Player &player)
{
    statemachine_.queueEvent(FIREPIT_ATTACK);
}

STATE_ENTER_FUNCTION(FirePit, FirePitOn, World, world)
{
    // t->fire_.setFillColor(sf::Color::Red);
}

STATE_UPDATE_FUNCTION(FirePit, FirePitOn, World, world)
{
    POLL_STATE_EVENTS(FirePit)
    {
        switch (event)
        {
        case FIREPIT_ATTACK:
            return STATE(FirePit, FirePitOff);
            break;

        default:
            break;
        }
    }

    if (t->intensity_ < 1.f)
    {
        t->intensity_ += elapsed.asSeconds() * 1;
        t->fire_.setFillColor(mixColor(sf::Color::Black, sf::Color::Red, t->intensity_));
    }

    return nullptr;
}

STATE_ENTER_FUNCTION(FirePit, FirePitOff, World, world)
{
    // t->fire_.setFillColor(sf::Color::Black);
}

STATE_UPDATE_FUNCTION(FirePit, FirePitOff, World, world)
{
    POLL_STATE_EVENTS(FirePit)
    {
        switch (event)
        {
        case FIREPIT_ATTACK:
            return STATE(FirePit, FirePitOn);
            break;

        default:
            break;
        }
    }

    if (t->intensity_ > 0.f)
    {
        t->intensity_ -= elapsed.asSeconds() * 1;
        t->fire_.setFillColor(mixColor(sf::Color::Black, sf::Color::Red, std::abs(t->intensity_)));
    }

    return nullptr;
}