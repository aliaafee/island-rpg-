#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <vector>
#include <queue>

class Node
{
public:
    int x;
    int y;
    float G;
    float H;
    float F;
    int parentIndex;
};

struct MoreThanByF
{
  bool operator()(const Node& lhs, const Node& rhs) const
  {
    return lhs.F > rhs.F;
  }
};

class Pathfinder
{
public:
    Pathfinder(const int &width, const int &height);
    ~Pathfinder();

private:
    int g_width_;
    int g_height_;

    int *grid_;
    Node *open_list;
    bool *closed_list_;

    std::priority_queue<Node, std::vector<Node>, MoreThanByF> w;

    int index_(const int &x, const int &y) const { return x + g_width_ * y; }
};

#endif // __PATHFINDER_H__