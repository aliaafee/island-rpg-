#ifndef __WORLDCELL_H__
#define __WORLDCELL_H__

#include <vector>
#include <random>

#include "Vector.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "Guides.hpp"
#include "SpiralOut.hpp"
#include "Vegetation.hpp"
#include "Ground.hpp"

class WorldConfig
{
public:
    WorldConfig(const float &width,
                const float &height,
                const int &cols,
                const int &rows) : width_(width),
                                   height_(height),
                                   cols_(cols),
                                   rows_(rows){};

    int getId(const int &i, const int &j) { return i + cols_ * j; }

    int getId(const Vector3f &point)
    {
        return getId(
            (int)std::floor(point.x / width_ * (float)cols_),
            (int)std::floor(point.y / height_ * (float)rows_));
    }

    bool validId(const int &id)
    {
        if (id < 0)
            return false;
        if (id > (width_ * height_ - 1))
            return false;
        return true;
    }

    bool validCell(const int &i, const int &j)
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

    Vector3f getCellPosition(const int &i, const int &j)
    {
        return Vector3f(
            (float)i / (float)cols_ * width_,
            (float)j / (float)rows_ * height_,
            0);
    }

    float getCellWidth()
    {
        return width_ / (float)cols_;
    }

    float getCellHeight()
    {
        return height_ / (float)rows_;
    }

    std::vector<std::pair<int, int>> getAdjacentIds(const Vector3f &point, const int &count)
    {
        return getAdjacentIds(
            (int)std::floor(point.x / width_ * (float)cols_),
            (int)std::floor(point.y / height_ * (float)rows_),
            count);
    }

    std::vector<std::pair<int, int>> getAdjacentIds(const int &i, const int &j, const int &count)
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

    const int &cols() const { return cols_; }
    const int &rows() const { return rows_; }

private:
    float width_, height_;
    int cols_, rows_;
};

class WorldCell
{
public:
    WorldCell(ResourceManager &rm,
              WorldConfig &worldConfig,
              const int &i, const int &j);

    int getId();

    std::vector<Entity *> &getEntities();

    void translateOrigin(const Vector3f &newOrigin);

private:
    Vector3f origin_;
    ResourceManager *rm_;
    WorldConfig *worldConfig_;
    int cell_i_, cell_j_;
    float width_, height_;
    Vector3f position_;

    std::vector<Entity *> entities_;
    std::vector<Entity *> placeholders_;
    Grid placeholder_;

    bool loaded_;
};

#endif // __WORLDCELL_H__