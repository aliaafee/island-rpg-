#include <iostream>
#include <chrono>

#include "../include/Pathfinder.hpp"

int main()
{
    std::cout << "# Testing Pathfinder" << std::endl;

    int g_width = 5000;
    int g_height = 5000;

    Pathfinder pf(g_width, g_height);

    std::vector<std::pair<int, int>> result;

    std::vector<int> grid;

    grid.resize(g_width * g_height);
    std::fill(grid.begin(), grid.end(), 1);
    grid[pf.gridIndex(0, 1)] = 0;
    grid[pf.gridIndex(5, 0)] = 0;
    grid[pf.gridIndex(5, 1)] = 0;
    grid[pf.gridIndex(5, 2)] = 0;
    grid[pf.gridIndex(5, 3)] = 0;
    grid[pf.gridIndex(5, 4)] = 0;
    grid[pf.gridIndex(5, 5)] = 0;
    grid[pf.gridIndex(5, 6)] = 0;
    grid[pf.gridIndex(5, 7)] = 0;
    grid[pf.gridIndex(5, 8)] = 1;
    grid[pf.gridIndex(5, 9)] = 0;

    int start_i = 1;
    int start_j = 2;
    int end_i = 9;
    int end_j = 5;

    pf.setGrid(grid);

    int reps = 10;
    bool found = false;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < reps; i++)
    {
        found = pf.searchAStar(start_i, start_j, end_i, end_j, true, result);
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    // for (auto &node : result)
    // {
    //     std::cout << node.first << ", " << node.second << "\n";
    // }

    // pf.printGrid(start_i, start_j, end_i, end_j, result);
    std::cout << "Path " << (found ? "" : "not ") << "found after " << pf.getRuns() << " runs."
              << "\n";
    std::cout << "Time for " << reps
              << " reps " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << "ms \n";
    std::cout << "Used " << pf.getNodesUsed() << " nodes. Reused " << pf.getNodesReused() << "\n";

    return 0;
}