#include <iostream>
#include <chrono>

#include "../include/Pathfinder.hpp"

int main()
{
    std::cout << "# Testing Pathfinder" << std::endl;

    long g_width = 1000;
    long g_height = 1000;

    std::cout << "Creating Pathfinder Instance.." << std::flush;
    Pathfinder pf(g_width, g_height);
    std::cout << "Done" << "\n";

    
    std::cout << "Creating Grid.." << std::flush;
    std::vector<int> grid;
    std::cout << grid.max_size() << " " << g_width * g_height << " ";
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
    std::cout << "Done" << "\n";

    int start_i = 1;
    int start_j = 2;
    int end_i = 900;
    int end_j = 500;

    std::cout << "Copying Grid.." << std::flush;
    pf.setGrid(grid);
    std::cout << "Done" << "\n";

    int reps = 10;
    bool found = false;

    std::cout << "Starting tests.." << std::flush;
    std::vector<std::pair<int, int>> result;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < reps; i++)
    {
        found = pf.searchAStar(start_i, start_j, end_i, end_j, true, result);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Done" << "\n";

    // for (auto &node : result)
    // {
    //     std::cout << node.first << ", " << node.second << "\n";
    // }

    if (g_width * g_height <= 100) {
        pf.printGrid(start_i, start_j, end_i, end_j, result);
    }
    std::cout << "Grid (" << g_width << "x" << g_height << ")\n";
    std::cout << "Path " << (found ? "" : "not ") << "found after " << pf.getRuns() << " runs."
              << "\n";
    std::cout << "Time for " << reps
              << " reps " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << "ms \n";
    std::cout << "Used " << pf.getNodesUsed() << " nodes. Reused " << pf.getNodesReused() << "\n";

    return 0;
}