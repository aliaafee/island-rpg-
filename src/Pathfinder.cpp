#include "Pathfinder.hpp"

Pathfinder::Pathfinder(const int &width, const int &height) : g_width_(width),
                                                              g_height_(height)
{
    grid_.resize(g_width_ * g_height_);
    std::fill(grid_.begin(), grid_.end(), 1);


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
    openList_.clear();
    closedList_.clear();

    // Add start node to open list
    Node *start = newNode(start_i, start_j, 0, 0, 0, nullptr);
    openList_[index_(start_i, start_j)] = start;
    openQueue_.push(start);

    Node *currentNode;
    float child_g, child_h, child_f;
    int currentNodeIndex, child_i, child_j, childIndex;
    int endIndex = index_(end_i, end_j);
    runs_ = 0;
    reusedNodes_ = 0;
    Node *newChild;
    std::unordered_map<int, bool>::iterator closedSearch;
    std::unordered_map<int, Node*>::iterator foundNode;
    while (!openQueue_.empty())
    {
        runs_ += 1;

        // Pop the openNode with lowest f
        currentNode = openQueue_.top();
        openQueue_.pop();
        currentNodeIndex = index_(currentNode->i, currentNode->j);

        // Make sure current node has not been closed yet
        closedSearch = closedList_.find(currentNodeIndex);
        if (closedSearch == closedList_.end())
        {
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
                        closedSearch = closedList_.find(childIndex);
                        if (closedSearch == closedList_.end())
                        {
                            child_g = currentNode->g + 1;
                            child_h = (end_i - child_i) * (end_i - child_i) + (end_j - child_j) * (end_j - child_j);
                            child_f = child_g + child_h;
                            foundNode = openList_.find(childIndex);
                            if (foundNode == openList_.end())
                            {
                                // Add child node to open list
                                newChild = newNode(
                                    child_i,
                                    child_j,
                                    child_g,
                                    child_h,
                                    child_f,
                                    currentNode);
                                openList_[index_(child_i, child_j)] = newChild;
                                openQueue_.push(newChild);
                            }
                            else
                            {
                                // Update the existing node
                                foundNode->second->g = child_g;
                                foundNode->second->h = child_h;
                                foundNode->second->f = child_f;
                                foundNode->second->parent = currentNode;
                                openQueue_.push(foundNode->second);
                                reusedNodes_ += 1;
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

    if (!diagonal)
    {
        return false;
    }

    int adj_i = i + (0 - i) + center_i;
    int adj_j = j + center_j;
    if (validIndex_(adj_i, adj_j))
    {
        if (grid_[index_(adj_i, adj_j)] == 0)
        {
            return false;
        }
    }

    adj_i = i + center_i;
    adj_j = j + (0 - j) + center_j;
    if (validIndex_(adj_i, adj_j))
    {
        if (grid_[index_(adj_i, adj_j)] == 0)
        {
            return false;
        }
    }

    return true;
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
    nodesUsed_ = nodeList_.size();
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

    for (int j = 0; j < g_height_; j++)
    {
        std::cout << " ";
        for (int i = 0; i < g_width_; i++)
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
                std::cout << "?";
                break;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}