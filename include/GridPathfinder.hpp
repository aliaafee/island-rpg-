#ifndef __GRIDPATHFINDER_H__
#define __GRIDPATHFINDER_H__

#include "Pathfinder.hpp"

class GridPathfinder : public Pathfinder
{
public:
    GridPathfinder(const Vector3f &position,
                   const float &width, const float &height,
                   const int &gridCols, const int &gridRows);

    void clearGrid();
    void setGrid(const std::vector<int> &grid);

    void setActiveGridArea(const int &cols, const int &rows);
    void addObstacle(const Entity &entity);

    virtual const int &cellValue(const int &i, const int &j) const;
    void setCellValue(const int &i, const int &j, const int &value);

    virtual bool validIndex(const int &i, const int &j) const;
    virtual bool validCell(const int &i, const int &j) const;

    void printGrid(const int &start_i, const int &start_j,
                   const int &end_i, const int &end_j,
                   const std::vector<std::pair<int, int>> &resultPath) const;

    void printGrid(const int &start_i, const int &start_j,
                   const int &end_i, const int &end_j) const;

private:
    std::vector<int> grid_;

    int zero_;

    int active_cols_;
    int active_rows_;
};

#endif // __GRIDPATHFINDER_H__