#ifndef __WORLDCONFIG_H__
#define __WORLDCONFIG_H__

#include "Vector.hpp"
#include "Algorithm.hpp"
#include "SimplexNoise.hpp"
#include "Camera.hpp"

class WorldConfig
{
public:
    WorldConfig(const float &width, const float &height,
                const int &cols, const int &rows,
                const int &subCols, const int &subRows,
                Camera &camera);

    int getId(const int &i, const int &j) { return i + cols_ * j; }
    int getId(const Vector3f &point);

    bool validId(const int &id);
    bool validCell(const int &i, const int &j);
    Vector3f getCellPosition(const int &i, const int &j);

    std::vector<std::pair<int, int>> getAdjacentIds(const Vector3f &point, const int &count);
    std::vector<std::pair<int, int>> getAdjacentIds(const int &i, const int &j, const int &count);

    const int &cols() const { return cols_; }
    const int &rows() const { return rows_; }

    const int &subCols() const { return subCols_; }
    const int &subRows() const { return subRows_; }

    float getCellWidth() { return width_ / (float)cols_; }
    float getCellHeight() { return height_ / (float)rows_; }

    float getElevation(const Vector3f &point) const;

    Camera *getCamera() const { return camera_; }

private:
    float width_, height_;
    int cols_, rows_;
    int subCols_, subRows_;

    SimplexNoise terrainNoise_;
    float terrainScale_ = 0.0009f;
    int terrainOctaves_ = 6;

    Camera *camera_;
};
#endif // __WORLDCONFIG_H__