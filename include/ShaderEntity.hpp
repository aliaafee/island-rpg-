#ifndef __SHADERENTITY_H__
#define __SHADERENTITY_H__

#include "Entity.hpp"


class ShaderEntity : public Entity
{
public:
    ShaderEntity(ResourceManager &rm);
    ~ShaderEntity();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    sf::Shader shader_;
    sf::RectangleShape rect_;

    sf::VertexArray arr;
    sf::RenderStates rs;
};

#endif // __SHADERENTITY_H__