#ifndef __ANIMATEDACTOR_H__
#define __ANIMATEDACTOR_H__

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SpriteActor.h"
#include "ResourceManager.h"

class AnimatedActor : public SpriteActor
{
public:
    AnimatedActor(ResourceManager *rm);
    ~AnimatedActor();

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

#endif // __ANIMATEDACTOR_H__