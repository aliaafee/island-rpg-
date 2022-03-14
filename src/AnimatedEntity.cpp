#include "AnimatedEntity.hpp"

AnimatedEntity::AnimatedEntity(ResourceManager &rm) : SpriteEntity(rm),
                                                    currentFrame(0),
                                                    currentAnimationName(""),
                                                    currentSequence(nullptr),
                                                    speed(10)
{
}

AnimatedEntity::~AnimatedEntity()
{
}

void AnimatedEntity::animate(sf::Time &elapsed)
{
    if (currentSequence == nullptr)
    {
        return;
    }

    currentFrame += speed * elapsed.asSeconds();
    if (floor(currentFrame) > currentSequence->size() - 1)
    {
        currentFrame = 0;
    }

    setTexture((*currentSequence)[floor(currentFrame)]);
}

void AnimatedEntity::setAnimationSpeed(const float &newSpeed)
{
    speed = newSpeed;
}

bool AnimatedEntity::setCurrentAnimation(const std::string &name)
{
    auto search = animations_.find(name);

    if (search == animations_.end())
    {
        return false;
    }

    currentAnimationName = name;
    currentSequence = &(search->second);

    setTexture(search->second[0]);
    return true;
}

bool AnimatedEntity::loadAnimation(const std::string &name, const std::string &directory)
{
    std::vector<sf::Texture *> sequence;

    if (!rm->loadTextureDirectory(directory, &sequence))
    {
        std::cout << "Failed to load animation " << directory << "\n";
        return false;
    }

    addAnimation(name, sequence);
    return true;
}

void AnimatedEntity::addAnimation(const std::string &name, const std::vector<sf::Texture *> &sequence)
{
    animations_.insert(std::pair(name, sequence));
}
