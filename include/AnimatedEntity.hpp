#ifndef __ANIMATEDENTITY_H__
#define __ANIMATEDENTITY_H__

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SpriteEntity.hpp"
#include "ResourceManager.hpp"

class AnimatedEntity : public SpriteEntity
{
public:
    AnimatedEntity(ResourceManager &rm);
    ~AnimatedEntity();

    virtual void animate(sf::Time &elapsed);

    void setAnimationSpeed(const float &newSpeed);
    bool setCurrentAnimation(const std::string &name);
    bool loadAnimation(const std::string &name, const std::string &directory);
    void addAnimation(const std::string &name, const std::vector<sf::Texture *> &sequence);

private:
    std::map<const std::string, std::vector<sf::Texture *>> animations_;

    float speed;
    std::string currentAnimationName;
    std::vector<sf::Texture *> *currentSequence;
    float currentFrame;
};

#endif // __ANIMATEDENTITY_H__