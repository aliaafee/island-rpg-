#include "WorldPathfinder.hpp"

WorldPathfinder::WorldPathfinder(const Vector3f &position,
                                 WorldConfig &worldConfig) : Pathfinder(position,
                                                                        worldConfig.getCellWidth() * 3.f,
                                                                        worldConfig.getCellHeight() * 3.f,
                                                                        worldConfig.subCols() * 3,
                                                                        worldConfig.subRows() * 3),
                                                             cellCols_(worldConfig.subCols()),
                                                             cellRows_(worldConfig.subRows()),
                                                             currentCells_{nullptr}
{
}

void WorldPathfinder::setActiveCells(const int &start_i, const int &start_j,
                                     const std::vector<WorldCell *> &activeCells)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            currentCells_[i][j] = nullptr;
        }
    }

    int i, j;
    for (auto &cell : activeCells)
    {
        i = cell->geti() - start_i;
        j = cell->getj() - start_j;
        currentCells_[i][j] = cell;
    }
}

bool WorldPathfinder::validCell(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return false;

    if (value_(i, j) == 0)
        return false;

    return true;
}

const int &WorldPathfinder::cellValue(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return ZERO;

    return value_(i, j);
}

const int &WorldPathfinder::value_(const int &i, const int &j) const
{
    int cell_i = i / cellCols_;
    int cell_j = j / cellRows_;

    int cell_id = i + j * 3;
    WorldCell *cell = currentCells_[cell_i][cell_j];

    if (cell == nullptr)
    {
        return ZERO;
    }

    return cell->obstacleGridValue(
        i - (cell_i * cellCols_),
        j - (cell_j * cellRows_));
}