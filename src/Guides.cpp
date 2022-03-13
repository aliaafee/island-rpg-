#include "Guides.hpp"

Grid::Grid(ResourceManager &rm,
           const float &width,
           const float &height,
           const int &gridCols,
           const int &gridRows) : Actor(rm),
                                  width_(width),
                                  height_(height),
                                  gridCols_(gridCols),
                                  gridRows_(gridRows),
                                  gridPoints2_(sf::Lines, gridCols_ * 2 + gridRows_ * 2),
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

    std::cout << "done " << std::endl;
}

void Grid::transform(Camera &camera)
{
    Actor::transform(camera);

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

    gridTransform2_ = sf::Transform();
    gridTransform2_.translate(getScreenPosition2());
}

void Grid::draw(sf::RenderTarget *screen)
{
    screen->draw(gridPoints2_, gridTransform2_);
}
