#include <iostream>
#include <chrono>

#include "../include/Pathfinder.hpp"

int main()
{
    std::cout << "# Testing Pathfinder" << std::endl;

    int reps = 1;
    float width = 100.f;
    float height = 100.f;
    int g_cols = 10;
    int g_rows = 10;
    int start_i = 1;
    int start_j = 2;
    int end_i = 9;
    int end_j = 5;

    std::cout << "Creating Pathfinder Instance.." << std::flush;
    Pathfinder pf(
        Vector3f(20.f, 10.f, 0.f),
        100.f, 100.f,
        g_cols, g_rows);
    pf.clearGrid();
    std::cout << "Done"
              << "\n";

    std::cout << "Creating Grid.." << std::flush;
    std::vector<int> grid;
    std::cout << grid.max_size() << " " << g_cols * g_rows << " ";
    grid.resize(g_cols * g_rows);
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
    std::cout << "Done"
              << "\n";

    std::cout << "Copying Grid.." << std::flush;
    pf.setGrid(grid);
    std::cout << "Done"
              << "\n";

    bool found = false;

    std::cout << "Starting tests.." << std::flush;
    // std::vector<std::pair<int, int>> result;
    std::deque<Vector3f> result;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < reps; i++)
    {
        // found = pf.searchAStar(start_i, start_j, end_i, end_j, true, result);
        found = pf.findPath(
            pf.toPoint(start_i, start_j),
            pf.toPoint(end_i, end_j),
            true,
            result);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Done"
              << "\n";

    // for (auto &node : result)
    // {
    //     std::cout << node.first << ", " << node.second << "\n";
    // }

    if (g_cols * g_rows <= 100)
    {
        pf.printGrid(start_i, start_j, end_i, end_j);
    }
    std::cout << "Grid (" << g_cols << "x" << g_rows << ")\n";
    std::cout << "Path " << (found ? "" : "not ") << "found after " << pf.getRuns() << " runs."
              << "\n";
    std::cout << "Time for " << reps
              << " reps " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << "ms \n";
    std::cout << "Used " << pf.getNodesUsed() << " nodes. Reused " << pf.getNodesReused() << "\n";

    return 0;
}