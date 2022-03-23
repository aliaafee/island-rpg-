#ifndef __GROUND_H__
#define __GROUND_H__

#include <algorithm>
#include <vector>

#include "Entity.hpp"
#include "SimplexNoise.hpp"
#include "WorldConfig.hpp"
#include "Algorithm.hpp"
#include "RandomGenerator.hpp"

class Ground : public Entity
{
public:
    Ground(ResourceManager &rm,
           const Vector3f &position,
           const float &width, const float &height,
           const int &cols, const int &rows,
           WorldConfig &worldConfig,
           RandomGenerator &r);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    float width_;
    float height_;
    int cols_;
    int rows_;
    float tileWidth_;
    float tileHeight_;

    Vector2f i_hat;
    Vector2f j_hat;

    sf::Sprite floorSprite_;
    sf::Texture floor_;
};
#endif // __GROUND_H__