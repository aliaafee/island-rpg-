#include "AnimatedActor.h"

AnimatedActor::AnimatedActor(ResourceManager *rm) : SpriteActor(rm),
                                                    currentFrame(0),
                                                    currentAnimationName(""),
                                                    currentSequence(nullptr),
                                                    speed(10)
{
}

AnimatedActor::~AnimatedActor()
{
}

void AnimatedActor::animate(sf::Time &elapsed)
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

void AnimatedActor::setAnimationSpeed(const float &newSpeed)
{
    speed = newSpeed;
}

bool AnimatedActor::setCurrentAnimation(const std::string &name)
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

bool AnimatedActor::loadAnimation(const std::string &name, const std::string &directory)
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

void AnimatedActor::addAnimation(const std::string &name, const std::vector<sf::Texture *> &sequence)
{
    animations_.insert(std::pair(name, sequence));
}
