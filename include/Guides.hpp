#ifndef __GUIDES_H__
#define __GUIDES_H__

#include <vector>

#include "Actor.hpp"

class Grid : public Actor
{
public:
    Grid(ResourceManager &rm,
         const float &width, const float &height,
         const int &gridCols, const int &gridRows);
    ~Grid();

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    float width_, height_, cellWidth_, cellHeight_;
    int gridCols_, gridRows_;

    bool transformed_;
    std::vector<Vector3f> gridPoints_;
    sf::VertexArray gridPoints2_;
    sf::Transform gridTransform2_;
};

#endif // __GUIDES_H__