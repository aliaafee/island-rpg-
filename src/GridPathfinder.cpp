#include "GridPathfinder.hpp"
GridPathfinder::GridPathfinder(const Vector3f &position,
                               const float &width,
                               const float &height,
                               const int &gridCols,
                               const int &gridRows) : Pathfinder(position,
                                                                 width,
                                                                 height,
                                                                 gridCols,
                                                                 gridRows),
                                                      active_cols_(gridCols),
                                                      active_rows_(gridRows)
{
    grid_.resize(gridCols * gridRows);
}

void GridPathfinder::clearGrid()
{
    std::fill(grid_.begin(), grid_.end(), ONE);
}

void GridPathfinder::setGrid(const std::vector<int> &grid)
{
    grid_ = grid;
}

void GridPathfinder::setActiveGridArea(const int &cols, const int &rows)
{
    active_cols_ = cols;
    active_rows_ = rows;
}

void GridPathfinder::addObstacle(const Entity &entity)
{
    Vector3f topLeft = entity.getPosition() - getPosition() - (entity.getSize() / 2.f);

    int start_i = (int)floor(topLeft.x / getCellWidth());
    int start_j = (int)floor(topLeft.y / getCellHeight());

    int end_i = (int)ceil((topLeft.x + entity.getSize().x) / getCellWidth());
    int end_j = (int)ceil((topLeft.y + entity.getSize().y) / getCellHeight());

    for (int i = start_i; i < end_i; i++)
    {
        for (int j = start_j; j < end_j; j++)
        {
            setCellValue(i, j, 0);
        }
    }
}

const int &GridPathfinder::cellValue(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return ZERO;

    return grid_[index(i, j)];
}

void GridPathfinder::setCellValue(const int &i, const int &j, const int &value)
{
    if (!validIndex(i, j))
        return;

    grid_[index(i, j)] = value;
}

bool GridPathfinder::validIndex(const int &i, const int &j) const
{
    if (i < 0)
        return false;
    if (i > active_cols_ - 1)
        return false;
    if (j < 0)
        return false;
    if (j > active_rows_ - 1)
        return false;
    return true;
}

bool GridPathfinder::validCell(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return false;

    if (grid_[index(i, j)] == ZERO)
        return false;

    return true;
}

void GridPathfinder::printGrid(const int &start_i, const int &start_j,
                               const int &end_i, const int &end_j,
                               const std::vector<std::pair<int, int>> &resultPath) const
{
    std::vector<int> grid = grid_;

    for (auto &node : resultPath)
    {
        grid[index(node.first, node.second)] = 80;
    }

    grid[index(start_i, start_j)] = 90;
    grid[index(end_i, end_j)] = 99;

    std::cout << "Grid (" << getCols() << "x" << getRows() << ")\n";

    for (int j = 0; j < getRows(); j++)
    {
        std::cout << " ";
        for (int i = 0; i < getCols(); i++)
        {
            switch (grid[index(i, j)])
            {
            case 1:
                std::cout << ".";
                break;
            case 0:
                std::cout << "#";
                break;
            case 90:
                std::cout << "S";
                break;
            case 99:
                std::cout << "E";
                break;
            case 80:
                std::cout << "X";
                break;
            default:
                std::cout << "?";
                break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void GridPathfinder::printGrid(const int &start_i, const int &start_j,
                               const int &end_i, const int &end_j) const
{
    printGrid(start_i, start_j, end_i, end_j, getLastResultPath());
}