#ifndef __WORLDPATHFINDER_H__
#define __WORLDPATHFINDER_H__

#include "Vector.hpp"
#include "Pathfinder.hpp"
#include "WorldConfig.hpp"
#include "WorldCell.hpp"

class WorldPathfinder : public Pathfinder
{
public:
    WorldPathfinder(const Vector3f &position, WorldConfig &worldConfig);

    void setActiveCells(const int &start_i, const int &start_j,
                        const std::vector<WorldCell *> &activeCells);

    virtual bool validCell(const int &i, const int &j) const;
    virtual const int &cellValue(const int &i, const int &j) const;

    void setValidCellValue(const int &value) { validCellValue_ = value; }

private:
    int cellCols_;
    int cellRows_;

    int validCellValue_;

    WorldCell *currentCells_[3][3];

    const int &value_(const int &i, const int &j) const;
};
#endif // __WORLDPATHFINDER_H__