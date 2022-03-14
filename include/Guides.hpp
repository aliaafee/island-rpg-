#ifndef __GUIDES_H__
#define __GUIDES_H__

#include <vector>

#include "Entity.hpp"
#include "Pathfinder.hpp"

class Grid : public Entity
{
public:
    Grid(const float &width, const float &height,
         const int &gridCols, const int &gridRows);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

protected:
    float width_, height_, cellWidth_, cellHeight_;
    int gridCols_, gridRows_;

private:
    bool transformed_;
    std::vector<Vector3f> gridPoints_;
    sf::VertexArray gridPoints2_;
    sf::Transform gridTransform2_;
};

class PathfinderGrid : public Grid
{
public:
    PathfinderGrid(Pathfinder &pathfinder);

    virtual void transform(Camera &camera);
    virtual void draw(sf::RenderTarget *screen);

private:
    Pathfinder *pathfinder_;

    Vector3f i_hat;
    Vector3f j_hat;

    std::vector<Vector3f> cellPoints_;
    sf::VertexArray cell_;
};

#endif // __GUIDES_H__