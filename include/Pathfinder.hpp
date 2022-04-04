#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <deque>
#include <cstring>

#include "Vector.hpp"
#include "Entity.hpp"
#include "Algorithm.hpp"

const int ZERO = 0;
const int ONE = 1;

class Node
{
public:
    Node() : parent(nullptr){};
    Node(const int &I, const int &J,
         const float &G, const float &H, const float &F,
         Node *Parent) : i(I), j(J), g(G), h(H), f(F), parent(Parent){};
    int i;
    int j;
    float g;
    float h;
    float f;
    Node *parent;
};

struct MoreThanByF
{
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        return lhs->f > rhs->f;
    }
};

class Pathfinder
{
public:
    Pathfinder(const Vector3f &position,
               const float &width, const float &height,
               const int &gridCols, const int &gridRows);
    ~Pathfinder();

    void setPosition(const Vector3f &position) { position_ = position; }
    const Vector3f &getPosition() const { return position_; }

    bool isAreaFree(const Vector3f &localPosition, const Vector3f &size) const;
    bool findFreeCell(const Vector3f &position, const int &maxDiameter, int &out_i, int &out_j) const;
    bool findFreePosition(const Vector3f &position, const int &maxDiameter, Vector3f &out_position) const;

    bool findPath(const Vector3f &start, const Vector3f &end,
                  const bool &diagonal,
                  std::deque<Vector3f> &resultPath);

    bool searchAStar(const int &start_i, const int &start_j,
                     const int &end_i, const int &end_j,
                     const bool &diagonal,
                     std::vector<std::pair<int, int>> &resultPath);

    const std::vector<std::pair<int, int>> &getLastResultPath() const { return resultPathCells_; }

    const int &getRuns() const { return runs_; }
    const int &getNodesUsed() const { return nodesUsed_; }
    const int &getNodesReused() const { return reusedNodes_; }

    void toGridCoord(const Vector3f &point, int &out_i, int &out_j) const;
    void toLocalGridCoord(const Vector3f &localPoint, int &out_i, int &out_j) const;
    Vector3f toPoint(const int &i, const int &j) const;
    Vector3f toLocalPoint(const int &i, const int &j) const;

    const int &cellValue(const Vector3f &point) const;

    const float &getWidth() const { return width_; }
    const float &getHeight() const { return height_; }
    const int &getCols() const { return g_cols_; }
    const int &getRows() const { return g_rows_; }
    const float &getCellWidth() const { return cellWidth_; }
    const float &getCellHeight() const { return cellHeight_; }

    int index(const int &i, const int &j) const { return i + g_cols_ * j; }

    virtual bool validIndex(const int &i, const int &j) const;

    // Pathfinder does not implement any method of storing cell values
    // these need to be overriden in child class
    virtual bool validCell(const int &i, const int &j) const = 0;
    virtual const int &cellValue(const int &i, const int &j) const = 0;

private:
    Vector3f position_;
    float width_;
    float height_;
    int g_cols_;
    int g_rows_;

    float cellWidth_;
    float cellHeight_;

    int runs_;
    int nodesUsed_;
    int reusedNodes_;

    std::vector<std::pair<int, int>> resultPathCells_;

    std::vector<Node *> nodeList_;

    std::unordered_map<int, Node *> openList_;

    std::unordered_map<int, bool> closedList_;

    std::priority_queue<Node *, std::vector<Node *>, MoreThanByF> openQueue_;

    Node *newNode(const int &I, const int &J,
                  const float &G, const float &H, const float &F,
                  Node *Parent);
    void cleanUp();

    bool validAdjacent_(const int &i, const int &j, const int &center_i, const int &center_j, const bool &diagonal) const;
};

#endif // __PATHFINDER_H__