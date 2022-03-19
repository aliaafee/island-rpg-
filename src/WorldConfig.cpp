#include "WorldConfig.hpp"

WorldConfig::WorldConfig(const float &width,
                         const float &height,
                         const int &cols,
                         const int &rows,
                         const int &subCols,
                         const int &subRows) : width_(width),
                                               height_(height),
                                               cols_(cols),
                                               rows_(rows),
                                               subCols_(subCols),
                                               subRows_(subRows),
                                               terrainNoise_()

{
    ;
}

int WorldConfig::getId(const Vector3f &point)
{
    return getId(
        (int)std::floor(point.x / width_ * (float)cols_),
        (int)std::floor(point.y / height_ * (float)rows_));
}

bool WorldConfig::validId(const int &id)
{
    if (id < 0)
        return false;
    if (id > (width_ * height_ - 1))
        return false;
    return true;
}

bool WorldConfig::validCell(const int &i, const int &j)
{
    if (i < 0)
        return false;
    if (j < 0)
        return false;
    if (i > cols_ - 1)
        return false;
    if (j > rows_ - 1)
        return false;
    return true;
}

Vector3f WorldConfig::getCellPosition(const int &i, const int &j)
{
    return Vector3f(
        (float)i / (float)cols_ * width_,
        (float)j / (float)rows_ * height_,
        0);
}

std::vector<std::pair<int, int>> WorldConfig::getAdjacentIds(const Vector3f &point, const int &count)
{
    return getAdjacentIds(
        (int)std::floor(point.x / width_ * (float)cols_),
        (int)std::floor(point.y / height_ * (float)rows_),
        count);
}

std::vector<std::pair<int, int>> WorldConfig::getAdjacentIds(const int &i, const int &j, const int &count)
{
    std::vector<std::pair<int, int>> r;
    if (validCell(i, j))
        r.push_back(std::pair(i, j));
    SpiralOut s(i, j, count - 1);
    int ai, aj;
    while (s.next(ai, aj))
    {
        if (validCell(ai, aj))
            r.push_back(std::pair(ai, aj));
    }
    return r;
}

float WorldConfig::getElevation(const Vector3f &point) const
{
    return terrainNoise_.fractal(
        6,
        point.x * terrainScale_,
        point.y * terrainScale_);
}