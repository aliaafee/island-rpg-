#include "Guides.hpp"

Grid::Grid(const float &width,
           const float &height,
           const int &gridCols,
           const int &gridRows) : width_(width),
                                  height_(height),
                                  gridCols_(gridCols),
                                  gridRows_(gridRows),
                                  gridPoints2_(sf::Lines),
                                  gridTransform2_(),
                                  transformed_(false)
{
    cellWidth_ = width_ / ((float)gridCols_);
    cellHeight_ = height_ / ((float)gridRows_);

    gridPoints_.resize(gridCols_ * 2 + gridRows_ * 2 + 4);

    int start = 0;
    for (int i = start; i < (start + (gridCols_ * 2)) + 2; i += 2)
    {
        gridPoints_[i].x = (float)(i - start) / 2.f * cellWidth_;
        gridPoints_[i].y = 0;

        gridPoints_[i + 1].x = (float)(i - start) / 2.f * cellWidth_;
        gridPoints_[i + 1].y = height_;
    }
    start += (gridCols_ * 2) + 2;
    for (int i = start; i < (start + (gridRows_ * 2)) + 2; i += 2)
    {
        gridPoints_[i].x = 0;
        gridPoints_[i].y = (float)(i - start) / 2.f * cellHeight_;

        gridPoints_[i + 1].x = width_;
        gridPoints_[i + 1].y = (float)(i - start) / 2.f * cellHeight_;
    }

    gridPoints2_.resize(gridPoints_.size());
}

void Grid::transform(Camera &camera)
{
    Entity::transform(camera);

    if (!transformed_)
    {
        Vector3f t;
        for (int i = 0; i < gridPoints_.size(); ++i)
        {
            t = camera.transform(gridPoints_[i], 0);
            gridPoints2_[i].position.x = t.x;
            gridPoints2_[i].position.y = t.y;
            gridPoints2_[i].color.r = 0;
            gridPoints2_[i].color.g = 0;
            gridPoints2_[i].color.b = 0;
            gridPoints2_[i].color.a = 100;
        }
        transformed_ = true;
    }

    gridTransform2_ = sf::Transform(1, 0, getScreenPosition().x,
                                    0, 1, getScreenPosition().y,
                                    0, 0, 1);
}

void Grid::draw(sf::RenderTarget *screen)
{
    screen->draw(gridPoints2_, gridTransform2_);
}

PathfinderGrid::PathfinderGrid(Pathfinder &pathfinder) : Grid(
                                                             pathfinder.getWidth(),
                                                             pathfinder.getHeight(),
                                                             pathfinder.getCols(),
                                                             pathfinder.getRows()),
                                                         pathfinder_(&pathfinder),
                                                         cell_(sf::Quads, 4)
{
    cellPoints_.resize(4);
    cellPoints_[0] = Vector3f(0, 0, 0);
    cellPoints_[1] = Vector3f(cellWidth_, 0, 0);
    cellPoints_[2] = Vector3f(cellWidth_, cellHeight_, 0);
    cellPoints_[3] = Vector3f(0, cellHeight_, 0);

    sf::Color col;
    col = sf::Color::Black;
    col.a = 100;

    cell_[0].color = col;
    cell_[1].color = col;
    cell_[2].color = col;
    cell_[3].color = col;
}

void PathfinderGrid::transform(Camera &camera)
{
    Grid::transform(camera);
    i_hat = camera.transform(Vector3f(cellWidth_, 0, 0), 0);
    j_hat = camera.transform(Vector3f(0, cellHeight_, 0), 0);

    Vector3f t;
    for (int i = 0; i < cellPoints_.size(); ++i)
    {
        t = camera.transform(cellPoints_[i], 0);
        cell_[i].position.x = t.x;
        cell_[i].position.y = t.y;
    }
}

void PathfinderGrid::draw(sf::RenderTarget *screen)
{
    Grid::draw(screen);

    Vector3f pos = getScreenPosition();
    Vector3f cellPos;
    for (int i = 0; i < gridCols_; i++)
    {
        for (int j = 0; j < gridRows_; j++)
        {
            if (pathfinder_->cellValue(i, j) == 0)
            {
                cellPos = pos + i_hat * (float)i + j_hat * (float)j;
                screen->draw(cell_, sf::Transform(1, 0, cellPos.x,
                                                  0, 1, cellPos.y,
                                                  0, 0, 1));
            }
        }
    }
}
