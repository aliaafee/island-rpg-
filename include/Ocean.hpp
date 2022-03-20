#ifndef __SHADERENTITY_H__
#define __SHADERENTITY_H__

#include "Entity.hpp"

class Ocean : public Entity
{
public:
    Ocean(ResourceManager &rm);
    ~Ocean();

    virtual void update(sf::Time &elapsed, World &world);
    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    sf::Clock clock_;
    sf::Shader shader_;
    bool shaderLoaded_;
    sf::RectangleShape rect_;

    sf::VertexArray arr;
    sf::RenderStates rs;
};

#endif // __SHADERENTITY_H__