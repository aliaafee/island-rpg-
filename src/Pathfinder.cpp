#include "Pathfinder.hpp"

Pathfinder::Pathfinder(const int &width, const int &height) : g_width_(width),
                                                              g_height_(height)
{
    grid_.resize(g_width_ * g_height_);
    std::fill(grid_.begin(), grid_.end(), 1);

    closedList_.resize(g_width_ * g_height_);
    std::fill(closedList_.begin(), closedList_.end(), false);

    openList_.resize(g_width_ * g_height_);
    std::fill(openList_.begin(), openList_.end(), nullptr);
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::setGrid(const std::vector<int> &grid)
{
    grid_ = grid;
}

bool Pathfinder::searchAStar(const int &start_i, const int &start_j,
                             const int &end_i, const int &end_j,
                             const bool &diagonal,
                             std::vector<std::pair<int, int>> &resultPath)
{
    if (!(validIndex_(start_i, start_j) && validIndex_(end_i, end_j)))
        return false;

    if ((start_i == end_i) && (start_j == end_j))
        return false;

    // Clear the data structures
    openQueue_ = std::priority_queue<Node *, std::vector<Node *>, MoreThanByF>();
    std::fill(openList_.begin(), openList_.end(), nullptr);
    std::fill(closedList_.begin(), closedList_.end(), false);

    // Add start node to open list
    Node *start = newNode(start_i, start_j, 0, 0, 0, nullptr);
    openList_[index_(start_i, start_j)] = start;
    openQueue_.push(start);

    Node *currentNode;
    float child_g, child_h, child_f;
    int currentNodeIndex, child_i, child_j, childIndex;
    int endIndex = index_(end_i, end_j);
    runs_ = 0;
    while (!openQueue_.empty())
    {
        runs_ += 1;

        // Pop the openNode with lowest f
        currentNode = openQueue_.top();
        openQueue_.pop();
        currentNodeIndex = index_(currentNode->i, currentNode->j);

        // Make sure current node has not been closed yet
        if (!closedList_[currentNodeIndex])
        {
            // Close the current Node
            closedList_[currentNodeIndex] = true;

            if (currentNodeIndex == endIndex)
            {
                // Reached the end backtrack and build the path from currentNode
                while (currentNode != nullptr)
                {
                    resultPath.insert(resultPath.begin(), std::pair(currentNode->i, currentNode->j));
                    currentNode = currentNode->parent;
                }

                cleanUp();
                return true;
            }

            // Look at all adjacent nodes
            for (int ci = -1; ci < 2; ci++)
            {
                for (int cj = -1; cj < 2; cj++)
                {
                    if (validAdjacent_(ci, cj, currentNode->i, currentNode->j, diagonal))
                    {
                        child_i = currentNode->i + ci;
                        child_j = currentNode->j + cj;
                        childIndex = index_(child_i, child_j);
                        // Check to see if child node is closed
                        if (!closedList_[childIndex])
                        {
                            // std::cout << child_i << ", " << child_j << "\n";
                            child_g = currentNode->g + 1;
                            child_h = (end_i - child_i) * (end_i - child_i) + (end_j - child_j) * (end_j - child_j);
                            child_f = child_g + child_h;
                            if (openList_[childIndex] == nullptr)
                            {
                                // Add child node to open list
                                openList_[childIndex] = newNode(
                                    child_i,
                                    child_j,
                                    child_g,
                                    child_h,
                                    child_f,
                                    currentNode);
                                openQueue_.push(openList_[childIndex]);
                            }
                            else
                            {
                                // Update the existing node
                                openList_[childIndex]->g = child_g;
                                openList_[childIndex]->h = child_h;
                                openList_[childIndex]->f = child_f;
                                openList_[childIndex]->parent = currentNode;
                                openQueue_.push(openList_[childIndex]);
                            }
                        }
                    }
                }
            }
        }
    }

    cleanUp();
    return false;
}

bool Pathfinder::validIndex_(const int &i, const int &j) const
{
    if (i < 0)
        return false;
    if (i > g_width_ - 1)
        return false;
    if (j < 0)
        return false;
    if (j > g_height_ - 1)
        return false;
    return true;
}

bool Pathfinder::validCell_(const int &i, const int &j) const
{
    if (!validIndex_(i, j))
        return false;

    if (grid_[index_(i, j)] == 0)
        return false;

    return true;
}

bool Pathfinder::validAdjacent_(const int &i, const int &j,
                                const int &center_i, const int &center_j,
                                const bool &diagonal) const
{
    if (!(abs(i) || abs(j)))
        return false;

    if (!validCell_(i + center_i, j + center_j))
        return false;

    if ((abs(i) != abs(j)))
    {
        return true;
    }

    return diagonal;
}

Node *Pathfinder::newNode(const int &I, const int &J,
                          const float &G, const float &H, const float &F,
                          Node *Parent)
{
    Node *n = new Node(I, J, G, H, F, Parent);
    nodeList_.push_back(n);
    return n;
}

void Pathfinder::cleanUp()
{
    for (auto &node : nodeList_)
        delete node;
    nodeList_.clear();
}

void Pathfinder::printGrid(const int &start_i, const int &start_j,
                           const int &end_i, const int &end_j,
                           const std::vector<std::pair<int, int>> &resultPath) const
{
    std::vector<int> grid = grid_;

    for (auto &node : resultPath)
    {
        grid[index_(node.first, node.second)] = 80;
    }

    grid[index_(start_i, start_j)] = 90;
    grid[index_(end_i, end_j)] = 99;

    std::cout << "Grid (" << g_width_ << "x" << g_height_ << ")\n";

    for (int j = 0; j < g_width_; j++)
    {
        std::cout << " ";
        for (int i = 0; i < g_height_; i++)
        {
            switch (grid[index_(i, j)])
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
                break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}