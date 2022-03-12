#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstring>

typedef std::pair<int, int> GridCell;

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
    Pathfinder(const int &width, const int &height);
    ~Pathfinder();

    void setGrid(const std::vector<int> &grid);

    bool searchAStar(const int &start_i, const int &start_j,
                     const int &end_i, const int &end_j,
                     const bool &diagonal,
                     std::vector<std::pair<int, int>> &resultPath);

    void printGrid(const int &start_i, const int &start_j,
                   const int &end_i, const int &end_j,
                   const std::vector<std::pair<int, int>> &resultPath) const;

    const int &getRuns() const { return runs_; }
    const int &getNodesUsed() const { return nodesUsed_; }
    const int &getNodesReused() const { return reusedNodes_; }

    int gridIndex(const int &i, const int &j) const { return index_(i, j); }

private:
    int g_width_;
    int g_height_;

    int runs_;
    int nodesUsed_;
    int reusedNodes_;

    std::vector<int> grid_;

    std::vector<Node *> nodeList_;

    std::map<GridCell,Node*> openList_;

    std::vector<bool> closedList_;

    std::priority_queue<Node *, std::vector<Node *>, MoreThanByF> openQueue_;

    Node *newNode(const int &I, const int &J,
                  const float &G, const float &H, const float &F,
                  Node *Parent);
    void cleanUp();

    int index_(const int &i, const int &j) const { return i + g_width_ * j; }
    bool validIndex_(const int &i, const int &j) const;
    bool validCell_(const int &i, const int &j) const;

    bool validAdjacent_(const int &i, const int &j, const int &center_i, const int &center_j, const bool &diagonal) const;
};

#endif // __PATHFINDER_H__