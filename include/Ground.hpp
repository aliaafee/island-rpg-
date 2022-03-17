#ifndef __GROUND_H__
#define __GROUND_H__

#include <vector>

#include "Entity.hpp"

class Ground : public Entity
{
public:
    Ground(ResourceManager &rm,
           const float &width, const float &height,
           const int &cols, const int &rows);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    std::vector<sf::Texture *> tiles_;
    std::vector<int> map_;

    float width_;
    float height_;
    int cols_;
    int rows_;
    float tileWidth_;
    float tileHeight_;

    Vector2f i_hat;
    Vector2f j_hat;

    sf::Sprite sprite_;
};
#endif // __GROUND_H__