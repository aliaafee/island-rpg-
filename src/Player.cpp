#include "Player.hpp"

STATE_INSTANCE_INIT(Player, PlayerIdleState);
STATE_INSTANCE_INIT(Player, PlayerRestingState);
STATE_INSTANCE_INIT(Player, PlayerWalkToState);
STATE_INSTANCE_INIT(Player, PlayerWalkState);
STATE_INSTANCE_INIT(Player, PlayerJumpState);
STATE_INSTANCE_INIT(Player, PlayerAttackingState);

Player::Player(ResourceManager &rm) : AnimatedEntity(rm),
                                      statemachine_(
                                          this,
                                          STATE(Player, PlayerIdleState)),
                                      animationDirection_("se"),
                                      animationAction_("swimming")
{
    std::string animationDirectory = "graphics/hunter/";

    std::string animationNames[6] = {"idle", "walking", "swimming", "treading", "sitting", "jumping"};

    std::string animationDirections[8] = {"sw",
                                          "s",
                                          "se",
                                          "e",
                                          "ne",
                                          "n",
                                          "nw",
                                          "w"};

    for (auto &name : animationNames)
    {
        // loadAnimation(name, animationDirectory + name);
        for (auto &direction : animationDirections)
        {
            std::string filename = animationDirectory + name + "/" + direction;
            loadAnimation(getAnimationName(name, direction), filename);
        }
    }

    setSpriteOrigin(68, 102);

    setAnimationSpeed(10);
}

void Player::update(sf::Time &elapsed, World &world)
{
    statemachine_.updateState(elapsed, world);

    animate(elapsed);
}

void Player::drawReflection(sf::RenderTarget *screen)
{
    if (inWater)
        return;
    AnimatedEntity::drawReflection(screen);
}

void Player::walkTo(const Vector3f &target)
{
    walkTarget_ = target;
    statemachine_.queueEvent(PLAYER_WALK_TARGET);
}

void Player::walkPath(const std::deque<Vector3f> &path)
{
    walkPath_ = path;
    statemachine_.queueEvent(PLAYER_WALK_TARGET);
}

void Player::attackOther(Entity &entity)
{
    attackingTarget_ = &entity;
    statemachine_.queueEvent(PLAYER_ATTACK_OTHER);
}

void Player::rest()
{
    statemachine_.queueEvent(PLAYER_REST);
}

void Player::setInWater(bool in)
{

    inWater = in;

    if (inWater)
    {
        setAnimationAction("treading");
        return;
    }

    setAnimationAction("idle");
}

void Player::stop()
{
    statemachine_.queueEvent(PLAYER_STOP);
}

void Player::setAnimationDirection(const std::string &direction)
{
    animationDirection_ = direction;
    setCurrentAnimation(getAnimationName(animationAction_, animationDirection_));
}

void Player::setAnimationDirection(const Vector3f &direction)
{
    float dir = std::atan2(direction.y, direction.x);

    if (dir < 0)
    {
        dir = std::abs(dir);
        if (dir > M_PI * 5.f / 8.f)
        {
            setAnimationDirection("n");
            return;
        }
        if (dir > M_PI * 3.f / 8.f)
        {
            setAnimationDirection("ne");
            return;
        }

        setAnimationDirection("e");
        return;
        return;
    }

    if (dir <= M_PI * 1.f / 8.f)
    {
        setAnimationDirection("se");
        return;
    }

    if (dir <= M_PI * 3.f / 8.f)
    {
        setAnimationDirection("s");
        return;
    }

    if (dir <= M_PI * 5.f / 8.f)
    {
        setAnimationDirection("sw");
        return;
    }

    if (dir <= M_PI * 7.f / 8.f)
    {
        setAnimationDirection("w");
        return;
    }

    setAnimationDirection("nw");
    return;
}

void Player::setAnimationAction(const std::string &action)
{
    animationAction_ = action;
    setCurrentAnimation(getAnimationName(animationAction_, animationDirection_));
}

std::string Player::getAnimationName(const std::string &action, const std::string &direction)
{
    return action + "_" + direction;
}

STATE_ENTER_FUNCTION(Player, PlayerIdleState, World, world)
{
    std::cout << "Player to Idle State" << std::endl;
    if (t->inWater)
    {
        t->setAnimationAction("treading");
        return;
    }
    t->setAnimationAction("idle");
}

STATE_UPDATE_FUNCTION(Player, PlayerIdleState, World, world)
{
    POLL_STATE_EVENTS(Player)
    {
        switch (event)
        {
        case PLAYER_WALK_TARGET:
            return STATE(Player, PlayerWalkToState);
            break;
        case PLAYER_ATTACK_OTHER:
            return STATE(Player, PlayerAttackingState);
            break;
        case PLAYER_REST:
            return STATE(Player, PlayerRestingState);
            break;
        default:
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        return STATE(Player, PlayerWalkState);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!t->inWater)
            return STATE(Player, PlayerJumpState);
    }

    return nullptr;
}

STATE_ENTER_FUNCTION(Player, PlayerRestingState, World, world)
{
    std::cout << "Player to Rest State" << std::endl;
    t->setAnimationAction("sitting");
}

STATE_ENTER_FUNCTION(Player, PlayerWalkState, World, world)
{
    if (t->inWater)
    {
        t->setAnimationAction("swimming");
        return;
    }
    t->setAnimationAction("walking");
}

STATE_UPDATE_FUNCTION(Player, PlayerWalkState, World, world)
{
    Vector3f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction.x += -1.f;
        direction.y += -1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction.y += 1.f;
        direction.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction.x += 1.f;
        direction.y += -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction.x += -1.f;
        direction.y += 1.f;
    }

    if (vecNull(direction))
        return STATE(Player, PlayerIdleState);

    vecNormalize(direction);

    float stepSize = t->walkSpeed_ * 60.f * elapsed.asSeconds();
    direction *= stepSize;

    Vector3f position = t->getLocalPosition();

    position.x += direction.x;
    if (!world.canMoveTo(*t, position))
        position.x = t->getLocalPosition().x;

    position.y += direction.y;
    if (!world.canMoveTo(*t, position))
        position.y = t->getLocalPosition().y;

    t->setLocalPosition(position);

    t->setAnimationDirection(direction);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!t->inWater)
            return STATE(Player, PlayerJumpState);
    }

    return nullptr;
}

STATE_ENTER_FUNCTION(Player, PlayerJumpState, World, world)
{
    t->setAnimationAction("jumping");
    t->vertSpeed = 1.5f;
    t->jumpCount = 2;
    t->jumpDelay = 0.5;
}

STATE_UPDATE_FUNCTION(Player, PlayerJumpState, World, world)
{
    CALL_STATE_UPDATE(PlayerWalkState, world);

    if (t->jumpDelay > 0.f)
    {
        t->jumpDelay -= elapsed.asSeconds();
        return nullptr;
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
    //     if (t->jumpCount < 2 && t->vertSpeed < 1.f)
    //     {
    //         t->jumpCount += 1;
    //         t->vertSpeed = 1.5;
    //     }
    // }

    t->vertSpeed -= 0.1 * 60 * elapsed.asSeconds();

    t->move(0, 0, t->vertSpeed * 60.f * elapsed.asSeconds());

    if (t->getLocalPosition().z < 0)
    {
        return STATE(Player, PlayerIdleState);
    }
    return nullptr;
}

STATE_ENTER_FUNCTION(Player, PlayerWalkToState, World, world)
{

    std::cout << "Player to Walk State" << std::endl;
    std::cout << "Finding Path.." << std::flush;
    t->walkPath_.clear();
    bool found = world.findPath(
        *t,
        t->walkTarget_,
        true,
        t->walkPath_);
    if (!found)
    {
        std::cout << "Not found\n";
        return;
    }
    std::cout << "Found\n";
    if (t->inWater)
    {
        t->setAnimationAction("swimming");
        return;
    }
    t->setAnimationAction("walking");
}

STATE_UPDATE_FUNCTION(Player, PlayerWalkToState, World, world)
{
    POLL_STATE_EVENTS(Player)
    {
        switch (event)
        {
        case PLAYER_STOP:
            return STATE(Player, PlayerIdleState);
            break;
        case PLAYER_WALK_TARGET:
            std::cout << "Recalc Path.." << std::flush;
            t->walkPath_.clear();
            bool found = world.findPath(
                *t,
                t->walkTarget_,
                true,
                t->walkPath_);
            if (!found)
            {
                std::cout << "Not found\n";
            }
            else
            {
                std::cout << "Found\n";
            }
            break;
        }
    }

    if (t->walkPath_.empty())
    {
        return STATE(Player, PlayerIdleState);
    }

    float stepSize = t->walkSpeed_ * 60.f * elapsed.asSeconds();
    Vector3f position;

    float distance2 = vecMagnitude2(t->toLocal(t->walkPath_.front()) - t->getLocalPosition());
    if (distance2 > stepSize * stepSize)
    {
        float distance = sqrt(distance2);
        Vector3f direction = (t->toLocal(t->walkPath_.front()) - t->getLocalPosition()) / distance;

        t->setAnimationDirection(direction);
        position = t->getLocalPosition() + direction * stepSize;
    }
    else
    {
        position = t->toLocal(t->walkPath_.front());
        t->walkPath_.pop_front();
    }

    if (!world.canMoveTo(*t, position))
    {
        // walkPath_.clear();
        // bool found = world.findPath(
        //     *this,
        //     walkTarget_,
        //     true,
        //     walkPath_);
        // if (!found)
        // {
        //     std::cout << "Not found\n";
        //     return idleStateId;
        // }
        // return walkStateId;
        return STATE(Player, PlayerIdleState);
    }

    t->setLocalPosition(position);

    return nullptr;
}

STATE_ENTER_FUNCTION(Player, PlayerAttackingState, World, world)
{
    if (t->attackingTarget_ == nullptr)
        return;

    float d = t->getSizeRadius() + t->attackingTarget_->getSizeRadius();
    if (vecDistance2(t->getLocalPosition(), t->attackingTarget_->getLocalPosition()) > d * d)
    {
        // t->walkTarget_ = t->attackingTarget_->getPosition();
        if (world.findNearbyFreePosition(t->attackingTarget_->getPosition(), t->walkTarget_))
        {
            CALL_STATE_ENTER(PlayerWalkToState, world);
        }
    }
}

STATE_UPDATE_FUNCTION(Player, PlayerAttackingState, World, world)
{
    if (t->attackingTarget_ == nullptr)
        return STATE(Player, PlayerIdleState);

    float d = t->getSizeRadius() + t->attackingTarget_->getSizeRadius();
    if (vecDistance2(t->getLocalPosition(), t->attackingTarget_->getLocalPosition()) > d * d)
    {
        CALL_STATE_UPDATE(PlayerWalkToState, world);
        return nullptr;
    }

    t->attackingTarget_->attack();

    t->attackingTarget_ = nullptr;

    return STATE(Player, PlayerIdleState);
}
