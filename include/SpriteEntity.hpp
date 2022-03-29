#ifndef __SPRITEENTITY_H__
#define __SPRITEENTITY_H__

#include <iostream>
#include <typeinfo>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ResourceManager.hpp"

class SpriteEntity : public Entity
{
public:
    SpriteEntity(ResourceManager &rm);
    ~SpriteEntity();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

    void setTexture(sf::Texture *texture);
    void setSpriteOrigin(const float &x, const float &y) { sprite_.setOrigin(x, y); }

    Vector2f getSpriteSize() const;

    FloatRect getSpriteRect() const;

    bool loadSprite(std::string filename);

private:
    sf::Sprite sprite_;
};

#endif // __SPRITEENTITY_H__