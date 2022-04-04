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

    virtual void drawReflection(sf::RenderTarget *screen);

    void setTexture(sf::Texture *texture);
    void setSpriteOrigin(const float &x, const float &y)
    {
        spriteOrigin_ = Vector2f(x, y);
        sprite_.setOrigin(spriteOrigin_);
    }

    Vector2f getSpriteSize() const;

    FloatRect getSpriteRect() const;

    bool loadSprite(std::string filename);

private:
    sf::Sprite sprite_;
    sf::Transform transform_;
    Vector2f spriteOrigin_;
};

#endif // __SPRITEENTITY_H__